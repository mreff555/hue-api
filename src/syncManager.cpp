#include "syncManager.h"
#include "smartField.h"
#include <thread>
#include <iostream>
#include <chrono>

SyncManager::SyncManager(std::shared_ptr<Command>(_command), std::shared_ptr<Hue::Device>(_deviceState)) 
: command(_command), deviceState(_deviceState)
{

}

void SyncManager::runEventLoop(bool &terminate)
{
    while(!terminate)
    {
        std::cout << "Tick\n";
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}


