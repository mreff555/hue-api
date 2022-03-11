#include "syncManager.h"
#include "smartField.h"
#include <thread>
#include <iostream>
#include <chrono>

// DEBUG
// #include <ctime>

SyncManager::SyncManager(std::shared_ptr<Command>(_command), std::shared_ptr<Hue::Device>(_deviceState)) 
: command(_command), deviceState(_deviceState)
{

}

void SyncManager::runEventLoop(bool &terminate)
{

    // //Debug
    // constexpr unsigned short lightnum = 6;
    // command->deviceContainer[lightnum].setName("Living Room 1");

    while(!terminate)
    {
        // refresh device data
        for(int i = 0; i < deviceArraySize; ++i)
        {
            command->refreshDataFromDevice(i);
        }

        // // DEBUG
        // time_t ts = command->deviceContainer->getTimeStamp();
        // std::cout << std::string(asctime(localtime(&ts)))
        //     << " - " << command->deviceContainer[lightnum].getName()
        //     << " - Status: " << command->deviceContainer[lightnum].getData().state.on << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}


