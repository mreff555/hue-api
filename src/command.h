#ifndef COMMAND_H
#define COMMAND_H

#include "config.h"
#include <string>
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>

class Command
{
  public:
  Command(std::shared_ptr<Config>);

  virtual ~Command();
  
  bool unauthorizedResponse();

  bool findHubIp();

  bool connect();

  // Public things that should probably be private
  //
  void post(const std::string, const std::string);

  void get(const std::string);

  void put(const std::string);

  private:
  CURL * curl;
  CURLcode res;

  static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);

  std::shared_ptr<Config> mCfg;

  // This stuff should be private
  public:
  std::string readBuffer;
  boost::property_tree::ptree jsonReadBuffer;

};

#endif /* COMMAND_H */

