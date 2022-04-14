#ifndef COMMAND_H
#define COMMAND_H

#include "config.h"
#include "deviceContainer.h"
#include <string>
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>

constexpr unsigned short deviceArraySize = 64;
constexpr Utility::milliseconds deviceRefreshThreshold = 2000;
constexpr Utility::milliseconds waitForButtonPressPingTimeInterval = 500;

class Command
{
  public:
  Command(std::shared_ptr<Config>);

  virtual ~Command();

  /**
   * @brief if the "deviceRefreshThreshold" has been exceeded, device data will be refreshed.
   * 
   * @param device id
   * @return true on success
   */
  bool refreshDataFromDevice(const unsigned short);

  /**
   * @brief Constructs the PUT statement to send a command.
   * 
   * @todo This should be private, however, do to the way I designed this, I'm finding
   * this rather difficult to accomplish.  Do later
   * @param _ip IP address of the HUE hub
   * @param _key user access key
   * @param _id device id [0 - 63]
   * @param _hue field Field to be set
   * @param _value the stringified value to be set
   */
  void setFieldAndSend(
    const std::string, 
    const std::string, 
    const unsigned int, 
    const Hue::HueFieldEnum, 
    std::string);

  std::string getHubIpAddress() const;

  std::string getAccessKey() const;

private:
  /**
   * @brief Queries the state of the jasosn read buffer to see if the most recent call produced an error
   * 
   * @return true on error found
   * @return false no error
   */
  bool unauthorizedResponse();

  /**
   * @brief Attempts to retrieve the local hub ip address using a GET call to https://discovery.meethue.com and save the value off to the current configuration
   * @return true if a not empty value is returned
   */
  bool findHubIp();

  /**
  * @brief Waits 30 seconds for a button press
  * 
  * @param N/A
  * @param message body
  * @return true on success
  */
  bool waitForButtonPress();

  /**
  * @brief Attempts to automatically locate a hub if required and authenticate or initiate pairing if required.
  * 
  * @param N/A
  * @return true on success
  */
  bool connect();

  /**
   * @brief Collect device data for the given id if available. This
   * function will not throw.  Returns the retrieved data regardless there
   * was an error.  Relies on other functions to diagnose if data was
   * acceptable.
   * 
   * @param device id The device id to retrieve data for [0 - 63]
   * @return On Error, will return error string, otherwise nothing.
   */
  std::string getDeviceData(const unsigned short);

  /**
  * @brief Perform a curl POST message.
  * @param url
  * @param message body
  * @return N/A
  */
  void post(const std::string, const std::string);

  /**
  * @brief Perform a curl GET message.
  * @param url
  * @return N/A
  */
  void get(const std::string);

  /**
   * @brief Perform a curl PUT operation
   * 
   * @param url
   * @param body 
   */
  void put(const std::string url, const std::string body);

  CURL * curl;

  CURLcode res;

  static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
  
  static size_t read_callback(char *ptr, size_t size, size_t nmemb, void *stream);

  template <typename T>
  std::vector<T> as_vector(boost::property_tree::ptree const& pt, boost::property_tree::ptree::key_type const& key);

  std::shared_ptr<Config> mCfg;

  std::string readBuffer;

  boost::property_tree::ptree jsonReadBuffer;
  
  DeviceContainer deviceContainer[deviceArraySize];
};

#endif /* COMMAND_H */

