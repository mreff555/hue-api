#include "command.h"
#include "deviceContainer.h"
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <thread>
#include <sstream>
#include <iostream>
#include <fcntl.h>
#include <ios>
#include <sstream>

Command::Command(std::shared_ptr<Config> _config) : mCfg(_config) 
{
  curl_global_init(CURL_GLOBAL_ALL);
  connect();

  for(int i = 0; i < deviceArraySize; ++i)
  {
    getDeviceData(i);
  }
}

Command::~Command()
{
  curl_global_cleanup();
}

bool Command::unauthorizedResponse()
{
  // TODO: This only makes sense when following a statemnt which attempted something requiring elevated
  // access.  Either the functionality needs to be expanded or it needs to be used differently.
  bool result = false;
  boost::optional<std::string> s = jsonReadBuffer.get_optional<std::string>(".error.description");
  if(s && s.get() == "unauthorized user")
    result = true;
  return result;
}

bool Command::findHubIp()
{
  bool result = false;
  this->get("https://discovery.meethue.com");
  boost::optional<std::string> id = jsonReadBuffer.get_optional<std::string>(".id");
  boost::optional<std::string> s = jsonReadBuffer.get_optional<std::string>(".internalipaddress");
 
  if(id)
    mCfg->setId(id.get());

  if(s)
  {
    mCfg->setInternalIpAddress(s.get());
    result = true;
  }

  return result;
}

bool Command::waitForButtonPress()
{
  bool success = false;
  if(mCfg->getUsername() == "")
  {
    std::cout << "Waiting 30 seconds for button press...\n";
    std::string url = "http://" + mCfg->getInternalIpAddress() + "/api";
    std::string body = "{\"devicetype\":\"hue_api#three_sheets\"}";
    for(int i = 0; i < 60; ++i)
    {
      post(url, body);
      boost::optional<std::string> username = jsonReadBuffer.get_optional<std::string>(".success.username");
      if(username)
      {
        mCfg->setUsername(username.get());
        std::cout << "success: " << mCfg->getUsername();
        success = true;
        break;
      }
      Utility::sleepMilliseconds(waitForButtonPressPingTimeInterval);
    }
  }
  else // Everything appears to be good
  {
    success = true;
  }
  if(success)
  {
    mCfg->write();
  }
  return success;
}

bool Command::connect()
{
  bool success = false;
  if(mCfg->getInternalIpAddress() == "" || mCfg->getUsername() == "")
  {
    success = findHubIp();
  }
  else
  {
    success = true;
  }
  if(success)
  {
    if(mCfg->getUsername() == "")
    {
      success = waitForButtonPress();
    }
    if(success && !unauthorizedResponse())
    {
      success = true;
    }
  } 
  else
  {
    success = false;
    std::cout << "Unable to locate hub\n";
  }
  return success;
}

std::string Command::getDeviceData(const unsigned short id)
{
  std::string returnString;
  readBuffer.clear();
  std::string url = mCfg->getInternalIpAddress() + "/api/" + mCfg->getUsername() + "/lights/" + std::to_string(id);
  get(url);
  auto errorType = jsonReadBuffer.get_optional<int>(".error.type");
  if(errorType.is_initialized())
  {
    returnString = "Error Type " + std::to_string(errorType.get()) + "\n";
  } 
  else 
  {
    returnString = readBuffer;
    
    auto xyVec = Command::as_vector<float>(jsonReadBuffer, "state.xy");
    Hue::Xy xy(xyVec[0], xyVec[1]);

    Hue::State state(
      jsonReadBuffer.get<bool>("state.on"),
      jsonReadBuffer.get<unsigned>("state.bri"),
      jsonReadBuffer.get<unsigned>("state.hue"),
      jsonReadBuffer.get<unsigned>("state.sat"),
      jsonReadBuffer.get<std::string>("state.effect"),
      xy,
      jsonReadBuffer.get<unsigned>("state.ct"),
      jsonReadBuffer.get<std::string>("state.alert"),
      jsonReadBuffer.get<std::string>("state.colormode"),
      jsonReadBuffer.get<std::string>("state.mode"),
      jsonReadBuffer.get<bool>("state.reachable")
    );

    Hue::SwUpdate swUpdate(
      jsonReadBuffer.get<std::string>("swupdate.state"),
      jsonReadBuffer.get<std::string>("swupdate.lastinstall")
    );

    Hue::Ct ct(
      jsonReadBuffer.get<unsigned>("capabilities.control.ct.min"),
      jsonReadBuffer.get<unsigned>("capabilities.control.ct.max")
    );

    // TODO: Figure out how to handle multi-dimensional vectors with property trees
    //auto colorGamutVec = Command::as_vector<float>(jsonReadBuffer, "capabilities.control.colorgamut");
    //float *colorGamutArr = &colorGamutVec[0];
    float colorGamutArr[3][2] = {};
    Hue::ControlCapabilities controlCapabilities(
      jsonReadBuffer.get<unsigned>("capabilities.control.mindimlevel"),
      jsonReadBuffer.get<unsigned>("capabilities.control.maxlumen"),
      jsonReadBuffer.get<std::string>("capabilities.control.colorgamuttype"),
      colorGamutArr,
      ct
    );

    Hue::StreamingCapabilities streamingCapabilities(
      jsonReadBuffer.get<bool>("capabilities.streaming.renderer"),
      jsonReadBuffer.get<bool>("capabilities.streaming.proxy")
    );

    Hue::Capabilities capabilities(
      jsonReadBuffer.get<bool>("capabilities.certified"),
      controlCapabilities,
      streamingCapabilities
    );

    Hue::StartUp startUp(
      jsonReadBuffer.get<std::string>("config.startup.mode"),
      jsonReadBuffer.get<bool>("config.startup.configured")
    );

    Hue::Config config(
      jsonReadBuffer.get<std::string>("config.archetype"),
      jsonReadBuffer.get<std::string>("config.function"),
      jsonReadBuffer.get<std::string>("config.direction"),
      startUp
    );

    Hue::Device device(
      state,
      swUpdate,
      jsonReadBuffer.get<std::string>("type"),
      jsonReadBuffer.get<std::string>("name"),
      jsonReadBuffer.get<std::string>("modelid"),
      jsonReadBuffer.get<std::string>("manufacturername"),
      jsonReadBuffer.get<std::string>("productname"),
      capabilities,
      config,
      jsonReadBuffer.get<std::string>("uniqueid"),
      jsonReadBuffer.get<std::string>("swversion"),
      jsonReadBuffer.get<std::string>("swconfigid"),
      jsonReadBuffer.get<std::string>("productid")
    );
    deviceContainer[id].setData(device);
  }

  deviceContainer[id].setTimeStamp();

  return returnString;
}

bool Command::refreshDataFromDevice(const unsigned short id)
{
  bool success = false;
  if((Utility::currentTimeInMilliseconds() - deviceContainer[id].getTimeStamp()) > deviceRefreshThreshold )
  {
    if(getDeviceData(id).find("Error") != std::string::npos)
    {
      success = true;
    }
  }
  return success;
}

void Command::post(const std::string url, const std::string body)
{
  curl = curl_easy_init();
  if(curl)
  {
    this->readBuffer.clear();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      std::cout << "error: " << curl_easy_strerror(res) << "\n";
    curl_easy_cleanup(curl);
    
    std::stringstream ss;
    ss << this->readBuffer;
    boost::property_tree::read_json(ss, jsonReadBuffer);
  }  
}

void Command::get(const std::string url)
{
  curl = curl_easy_init();
  if(curl)
  {
    this->readBuffer.clear();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      std::cout << "error: " << curl_easy_strerror(res) << "\n";
    curl_easy_cleanup(curl);
    
    std::stringstream ss;
    ss << this->readBuffer;
    boost::property_tree::read_json(ss, jsonReadBuffer);
  }
}

void Command::put(const std::string url, const std::string body)
{

  CURLcode ret;
  struct curl_slist *slist1;
  slist1 = NULL;
  slist1 = curl_slist_append(slist1, "Content-Type: multipart/form-data;");
  curl = curl_easy_init();
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)12);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.79.1");
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_SSH_KNOWNHOSTS, "/Users/$USER/.ssh/known_hosts");
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, 1L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

    ret = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;
  }
  curl_easy_cleanup(curl);
  curl = nullptr;
  curl_slist_free_all(slist1);
  slist1 = NULL;
}
  
size_t Command::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

size_t read_callback(char *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t retcode;
  curl_off_t nread;
 
  /* in real-world cases, this would probably get this data differently
     as this fread() stuff is exactly what the library already would do
     by default internally */
  retcode = fread(ptr, size, nmemb, static_cast<FILE*>(stream));
 
  nread = (curl_off_t)retcode;
 
  fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
          " bytes from file\n", nread);
 
  return retcode;
}

template <typename T>
std::vector<T> Command::as_vector(boost::property_tree::ptree const& pt, boost::property_tree::ptree::key_type const& key)
{
    std::vector<T> r;
    for (auto& item : pt.get_child(key))
        r.push_back(item.second.get_value<T>());
    return r;
}
