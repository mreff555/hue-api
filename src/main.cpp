#include "config.h"
#include "command.h"
#include "device.h"
#include "syncManager.h"
#include <memory>
#include <iostream>
#include <signal.h>

/* Terminate processing flag */
bool terminate = false;
  
void sigHandler(int signum)
{
  terminate = true;
  printf("Terminated on sig %d\n", signum); 
}

int main()
{

  /* Signal traps for various inturrupts       */
  signal(SIGINT, sigHandler);  /* Ctrl + C     */
  signal(SIGQUIT, sigHandler); /* Ctrl + D     */
  signal(SIGHUP, sigHandler);  /* On pty close */
  signal(SIGTERM, sigHandler); /* On term sig  */

  auto cfg = std::make_shared<Config>();
  auto cmd = std::make_shared<Command>(cfg);
  auto dev = std::make_shared<Hue::Device>();
  auto mgr = std::make_shared<SyncManager>(cmd, dev);

  // Hue::Xy xy(3,5);

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

