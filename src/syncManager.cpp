#include "syncManager.h"
#include "timeUtil.h"
#include <iostream>

SyncManager::SyncManager(
    std::shared_ptr<Command>(_command), 
    std::shared_ptr<Hue::Device>(_deviceState)) 
: command(_command), 
deviceState(_deviceState)
{
    // Debug
    Task tsk(Hue::STATE_ON, 6, "true");
    taskVector.push_back(tsk);
}

void SyncManager::runEventLoop(bool &terminate)
{

    //Debug
    // constexpr unsigned short lightnum = 6;
    // command->deviceContainer[lightnum].setName("Living Room 1");

    while(!terminate)
    {
        // refresh device data
        for(int i = 0; i < deviceArraySize; ++i)
        {
            command->refreshDataFromDevice(i);
        }

        // Perform scheduled tasks
        for(auto task : taskVector)
        {
            auto taskId = task.getId();
            command->
            //auto data = command->deviceContainer[taskId].getDataBuffer();
        }

        // // DEBUG
        // std::cout << Utility::currentTime()
        //     << " - " << command->deviceContainer[lightnum].getName()
        //     << " - Status: " << command->deviceContainer[lightnum].getData().state.on << "\n";

        Utility::sleepMilliseconds(interval);
    }
}


