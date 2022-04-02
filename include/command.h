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
   * @brief Turn the specified light on/off
   * 
   * @param _lightId value representing a light RANGE [0 - 63]
   * @param _on [DEFAULT = true]
   */
  void setLightOn(const unsigned short _lightId, bool _on = true);

  /**
   * @brief Set the brightness for the specified light
   * 
   * @param _lightId 
   * @param _value positive integer RANGE [0 - 254]
   * 
   * @return true on success
   */
  bool setLightBrightness(const unsigned short _lightId, const unsigned short _value);

  /**
   * @brief Set the hue for the specified light
   * 
   * @param _lightId 
   * @param _value positive integer RANGE [0 - 65535]
   * 
   * @return true on success
   */
  bool setLightHue(const unsigned short _lightId, const unsigned short _value);

  /**
   * @brief Set the saturation for the specified light
   * 
   * @param _lightId 
   * @param _value positive integer RANGE [0 - 254]
   * 
   * @return true on success
   */
  bool setLightSaturation(const unsigned short _lightId, const unsigned short _value);

  /**
   * @brief Set the color for the specified light by X/Y coordinates
   * 
   * @param _lightId 
   * @param _x RANGE [0 - 1]
   * @param _y RANGE [0 - 1]
   * 
   * @return true on success
   */
  bool setLightColorXY(const unsigned short _lightId, const float _x, float _y);

  /**
   * @brief if the "deviceRefreshThreshold" has been exceeded, device data will be refreshed
   * 
   * @param device id
   * @return true on success
   */
  bool refreshDataFromDevice(const unsigned short);

  /**
   * @brief Set the Field And Send object
   * 
   * @return true 
   * @return false 
   */
  bool setFieldAndSend(
    const std::string, 
    const std::string, 
    const unsigned int, 
    const Hue::HueFieldEnum, 
    std::string);

  // private:
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
   * @brief Collect device data for the given id if available
   * 
   * @param device id
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
  
  // TODO: should not be public
  public:
  // Hue::Device deviceArray[deviceArraySize];
  DeviceContainer deviceContainer[deviceArraySize];
};

#endif /* COMMAND_H */

