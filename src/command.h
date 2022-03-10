#ifndef COMMAND_H
#define COMMAND_H

#include "config.h"
#include "device.h"
#include "deviceContainer.h"
#include <string>
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>
constexpr unsigned short deviceArraySize = 64;

class Command
{
  public:
  Command(std::shared_ptr<Config>);

  virtual ~Command();

  bool unauthorizedResponse();

  bool findHubIp();

  /**
  * @brief Waits 30 seconds for a button press
  * @param N/A
  * @param message body
  * @return true on success
  */
  bool waitForButtonPress();

  /**
  * @brief Attempts to automatically locate a hub if required and authenticate or initiate pairing if required.
  * @param N/A
  * @return true on success
  */
  bool connect();

  // std::vector<unsigned short> getDeviceVector();

  /**
   * @brief Collect device data for the given id if available
   * 
   * @param device id
   */
  std::string getDeviceData(const unsigned int);

  /**
  * @brief Initiate a http POST message.
  * @param url
  * @param message body
  * @return N/A
  */
  void post(const std::string, const std::string);

  /**
  * @brief Initiate a http GET message.
  * @param url
  * @return N/A
  */
  void get(const std::string);

  void put(const std::string url, const std::string body);

  private:
  CURL * curl;

  CURLcode res;

  static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
  
  static size_t read_callback(char *ptr, size_t size, size_t nmemb, void *stream);

  template <typename T>
  std::vector<T> as_vector(boost::property_tree::ptree const& pt, boost::property_tree::ptree::key_type const& key);

  std::shared_ptr<Config> mCfg;

  std::string readBuffer;

  boost::property_tree::ptree jsonReadBuffer;
  
  public:
  // Hue::Device deviceArray[deviceArraySize];
  DeviceContainer deviceContainer[deviceArraySize];
};

#endif /* COMMAND_H */

