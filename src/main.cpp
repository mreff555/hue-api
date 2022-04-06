#include "config.h"
#include "command.h"
#include "device.h"
#include "syncManager.h"
#include "console.h"

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
  auto configuration = std::make_shared<Config>();

  /**
   * @brief Handles the calls to the API, and some initialization procedures
   * 
   */
  auto command = std::make_shared<Command>(configuration);

  /**
   * @brief A memory database reflecting hue capabilities
   * 
   */
  auto deviceData = std::make_shared<Hue::Device>();

  /**
   * @brief Responsible for the state management of all devices
   * 
   */
  auto syncManager = std::make_shared<SyncManager>(
    command, deviceData);

  /**
   * @brief A semi-graphical management console using notcurses
   * 
   */
  // auto tuiManagementConsole = std::make_shared<Console>(); 

  // DEBUG

  // commandWrapper->setLightOn(6);
  // commandWrapper->setLightBrightness(6, 30);
  // for(auto i = 0; i < deviceArraySize; i += 650)
  // {
  //   commandWrapper->setLightHue(6, i);
  //   Utility::sleepMilliseconds(100);
  // }

  // commandWrapper->setLightOn(6);
  // commandWrapper->setLightBrightness(6,250);
  // commandWrapper->setLightColorXY(6,0.3,0.79);

  // end DEBUG

  std::thread syncManagerThread(&SyncManager::runEventLoop, syncManager, std::ref(terminate));
  // std::thread tuiManagementConsoleThread(&Console::runEventLoop, tuiManagementConsole, std::ref(terminate));

  // tuiManagementConsoleThread.join();
  syncManagerThread.join();

  return 0;
}

