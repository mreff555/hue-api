#include "command.h"
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>

Command::Command(std::shared_ptr<Config> _config) : mCfg(_config) 
{
  curl_global_init(CURL_GLOBAL_ALL);
}

Command::~Command()
{
  curl_global_cleanup();
}

bool Command::unauthorizedResponse()
{
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

// Attempts to retrieve hub Ip if it is not already known.
// Tests to see if client can authenticate.  Breaks loop
// if a username is retrieved;
bool Command::connect()
{
  bool foundIp = false;
  if(unauthorizedResponse())
  {
    if(mCfg->getUsername() == "")
    {
      foundIp = findHubIp();
    }

    if(foundIp)
    {
      std::cout << "Waiting 30 seconds for button press...\n";
      std::string url = "http://";
      url += mCfg->getInternalIpAddress();
      url += "/api";

      // TODO: This is a temporary copy and paste until I can figure out
      // more about these device types
      std::string body = "{\"devicetype\":\"my_hue_app#iphone peter\"}";
      
      for(int i = 0; i < 60; ++i)
      {
        post(url, body);
        boost::optional<std::string> username =jsonReadBuffer.get_optional<std::string>("success.username");
        if(username)
        {
          mCfg->setUsername(username.get());
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    } /* foundIp */
  } /* if(unauthorizedResponse()) */
  return !unauthorizedResponse(); // returns 1 if connected;
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

void Command::put(const std::string){}
  
size_t Command::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}
