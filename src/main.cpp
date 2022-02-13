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

  cmd->getDeviceData(6);
  std::cout << "On: " << cmd->deviceArray[6].state.on << "\n";
  std::cout << "Brightness: " << cmd->deviceArray[6].state.bri << "\n";
  std::cout << "Hue: " << cmd->deviceArray[6].state.hue << "\n";
  std::cout << "Saturation : " << cmd->deviceArray[6].state.sat << "\n";
  std::cout << "Max Lumen : " << cmd->deviceArray[6].capabilities.control.maxlumen << "\n";

  return 0;
}

