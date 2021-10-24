#include "config.h"
#include "command.h"
#include <memory>
#include <iostream>

// Very simple config file template and demo
// read and write calls are overloaded with string
// parameters, otherwise the default location defined
// in the header is used.  A timestamp is set when writing
// the file.  It does not seem to be saving off the full
// 64 bits of information.  I'll have to look into this later
// but this still should be good down to seconds, which is fine
// for most config file timestamps.
//
// compile with -lboost_system

int main()
{
  std::shared_ptr<Config> cfg = std::make_shared<Config>();
  std::shared_ptr<Command> cmd = std::make_shared<Command>(cfg);

  cfg->setUrl("192.168.1.7");
  cfg->write();
  cmd->post("192.168.1.7/api","{\"devicetype\":\"my_hue_app#iphone peter\"}");
  std::cout << cmd->readBuffer << "\n";
  boost::property_tree::write_json(std::cout, cmd->jsonReadBuffer);

  cmd->get("https://discovery.meethue.com");
  std::cout << cmd->readBuffer << "\n";
  boost::property_tree::write_json(std::cout, cmd->jsonReadBuffer);

  if(cmd->findHubIp())
  {
    std::cout << cfg->getInternalIpAddress() << "\n";
  }
  else
  {
    std::cout << "error retrieving ip\n";
  }
  //std::cout << cmd->readBuffer << "\n";


  return 0;
}
