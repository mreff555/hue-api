#include "config.h"
#include "command.h"
#include <memory>
#include <iostream>

int main()
{
  auto cfg = std::make_shared<Config>();
  auto cmd = std::make_shared<Command>(cfg);

  Hue::Xy xy(3,5);

  // cmd->getDeviceData(6);
  // std::cout << "On: " << cmd->deviceArray[6].state.on << "\n";
  // std::cout << "Brightness: " << cmd->deviceArray[6].state.bri << "\n";
  // std::cout << "Hue: " << cmd->deviceArray[6].state.hue << "\n";
  // std::cout << "Saturation : " << cmd->deviceArray[6].state.sat << "\n";
  // std::cout << "Product Name : " << cmd->deviceArray[6].productname << "\n";
  // std::cout << "Max Lumen : " << cmd->deviceArray[6].capabilities.control.maxlumen << "\n";
  // std::cout << "Function : " << cmd->deviceArray[6].config.function << "\n";

  //cmd->put("http://192.168.1.7/api/14ieK0ZYTBJ2lH76RvqYlPP7fiJeXvZDrkpJ6A2-/lights/6/state", "{\"on\":false}");

//Hue::Xy xy(4,5);
//std::cout << xy.x.getBody() << "\n";

  return 0;
}

