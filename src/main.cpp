/**
 * @file main.cpp
 * @author Dan Feerst (feerstd@gmail.com)
 * @brief hue_server tracks the state of all lights on a given hub.
 * It can set values, and perform sequences of events
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "config.h"
#include "command.h"
#include "device.h"
#include "syncManager.h"
#include "hue_server_interface.h"
#include "console.h"

#include <thread>
#include <memory>
#include <iostream>
#include <signal.h>

/* Terminate processing flag */
bool terminate = false;

/**
 * @brief Callback for signal traps used to terminate the application gracefully
 * 
 * @param signum signal value 
 */
void sigHandler(int signum)
{
  terminate = true;
  printf("Terminated on sig %d\n", signum); 
}

/**
 * @brief This is the entry point for the hue_server
 * 
 * @return Always returns zer0
 */
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

  auto hueServerInterface = std::make_shared<HueServerInterface>(
    syncManager);

  /**
   * @brief A semi-graphical management console using notcurses
   * 
   */
  // auto tuiManagementConsole = std::make_shared<Console>(); 

  std::thread syncManagerThread(&SyncManager::runEventLoop, syncManager, std::ref(terminate));
  // std::thread tuiManagementConsoleThread(&Console::runEventLoop, tuiManagementConsole, std::ref(terminate));

  // debug
  // syncManager->addTask({Hue::STATE_ON, 6, "false"});
  // syncManager->addTask({Hue::STATE_BRI, 6, "1"});
  // syncManager->addTask({Hue::STATE_HUE, 6, "1500"});

  // tuiManagementConsoleThread.join();
  syncManagerThread.join();

  return 0;
}

