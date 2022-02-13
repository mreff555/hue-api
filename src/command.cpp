#include "command.h"
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>
#include <fcntl.h>
#include <ios>
#include <sstream>

Command::Command(std::shared_ptr<Config> _config) : mCfg(_config) 
{
  curl_global_init(CURL_GLOBAL_ALL);
  connect();
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
  
    // TODO: This is a temporary copy and paste until I can figure out more about these device types
    // The way I understand it now, this should be some type of UUID.  It's value is probably a seed
    // for the generated username when you press the id. 
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
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

// I don't really know what I am going to do with this yet,
// but I THINK it's a logical next step.  The output vector
// is a list of numbers representing active devices.
// Maybe this should be a map, and maybe it should point
// to something useful.  Maybe it shouldn't be in this class.
// All things to contemplate. 
std::vector<unsigned short> Command::getDeviceVector()
{
  std::vector<unsigned short> vec;
  std::string url = mCfg->getInternalIpAddress() + "/api/" + mCfg->getUsername() + "/lights";
  get(url);
  std::string str;
  for(int i = 0; i < 32; ++i)
  {
    str.clear();
    str = std::to_string(i) + ".state.reachable";
    boost::optional<bool> reachable = jsonReadBuffer.get_optional<bool>(str);
    if(reachable)
    {
      vec.push_back(i);
      std::cout << i << "\n";
    }
  }
}

void Command::getDeviceData(const unsigned int id)
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

    // TODO: Finish the rest of the device 

    Hue::Device device;
    device.state = state;
    device.swupdate = swUpdate;
    device.capabilities = capabilities;
    // TODO: Make sure you add everything to the device;
    deviceArray[id] = device; 
  }
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
    // curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    // curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
    // curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    // curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
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
  curl = curl_easy_init();
  if(curl)
  {
    std::stringstream ss;
    ss << body;
    ss.seekg(0, std::ios::end);
    int size = ss.tellg();

    // this->readBuffer.clear();
    // curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    // curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    // curl_easy_setopt(curl, CURLOPT_READDATA, body);
    // curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)size);
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    // // curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
    // res = curl_easy_perform(curl);
    // if(res != CURLE_OK)
    //   std::cout << "error: " << curl_easy_strerror(res) << "\n";
    // curl_easy_cleanup(curl);
    
    // std::stringstream ss;
    // ss << this->readBuffer;
    // boost::property_tree::read_json(ss, jsonReadBuffer);
  }  
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
