#include "config.h"
#include "command.h"
#include "device.h"
#include "syncManager.h"
#include "console.h"

//DEBUG
#include "timeUtil.h"

#include <thread>
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

  /**
   * @brief Loads and saves select information in JSON format
   * 
   */
  auto cfg = std::make_shared<Config>();

  /**
   * @brief Handles the calls to the API, and some initialization procedures
   * 
   */
  auto cmd = std::make_shared<Command>(cfg);

  /**
   * @brief A memory database reflecting hue capabilities
   * 
   */
  auto dev = std::make_shared<Hue::Device>();

  /**
   * @brief Responsible for the state management of all devices
   * 
   */
  auto syncManager = std::make_shared<SyncManager>(cmd, dev);

  /**
   * @brief A semi-graphical management console using notcurses
   * 
   */
  auto tuiManagementConsole = std::make_shared<Console>(); 

  // DEBUG
  cmd->setFieldAndSend(cfg->getInternalIpAddress(), cfg->getUsername(), 6, Hue::STATE_ON, std::string("true"));
  Utility::sleepSeconds(2);
  cmd->setFieldAndSend(cfg->getInternalIpAddress(), cfg->getUsername(), 6, Hue::STATE_HUE, std::string("120"));
  Utility::sleepSeconds(2);
  cmd->setFieldAndSend(cfg->getInternalIpAddress(), cfg->getUsername(), 6, Hue::STATE_HUE, std::string("240"));
  Utility::sleepSeconds(2);
    cmd->setFieldAndSend(cfg->getInternalIpAddress(), cfg->getUsername(), 6, Hue::STATE_HUE, std::string("0"));
  Utility::sleepSeconds(2);
  cmd->setFieldAndSend(cfg->getInternalIpAddress(), cfg->getUsername(), 6, Hue::STATE_ON, std::string("false"));
  // end DEBUG

  std::thread syncManagerThread(&SyncManager::runEventLoop, syncManager, std::ref(terminate));
  std::thread tuiManagementConsoleThread(&Console::runEventLoop, tuiManagementConsole, std::ref(terminate));

  tuiManagementConsoleThread.join();
  syncManagerThread.join();
  

  // Hue::Xy xy(3,5);

  // cmd->deviceContainer[28].setName("Max's Room");
  // for(int i = 0; i < deviceArraySize; ++i)
  // {
  //   std::cout << i << ": " 
  //     << cmd->deviceContainer[i].getName() 
  //     << " - on: " << cmd->deviceContainer[i].getData().state.on 
  //     << "\t" << cmd->deviceContainer[i].getTimeStamp() << "\n";
  // }
  // std::cout << "Brightness: " << cmd->deviceArray[lightId].state.bri << "\n";
  // std::cout << "Hue: " << cmd->deviceArray[lightId].state.hue << "\n";
  // std::cout << "Saturation : " << cmd->deviceArray[lightId].state.sat << "\n";
  // std::cout << "Product Name : " << cmd->deviceArray[lightId].productname << "\n";
  // std::cout << "Max Lumen : " << cmd->deviceArray[lightId].capabilities.control.maxlumen << "\n";
  // std::cout << "Function : " << cmd->deviceArray[lightId].config.function << "\n";

  // cmd->put("http://192.168.1.7/api/14ieK0ZYTBJ2lH76RvqYlPP7fiJeXvZDrkpJ6A2-/lights/4/state", "{\"on\":false}");

//Hue::Xy xy(4,5);
//std::cout << xy.x.getBody() << "\n";

  return 0;
}

