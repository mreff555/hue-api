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
        // TODO: I can forsee to really big problems with this for-loop
        // TODO: as is.  First, I'm going to need a mutex, or something
        // TODO: similar to prevent adding elements to the vector while
        // TODO: tasks are being executed.  Either that or put the addition
        // TODO: mechanism within the for loop.  The other problem is that
        // TODO: at some point I am going to have to limit the number of
        // TODO: limit the actions performed before cycling.
        for(auto task : taskVector)
        {
            command->setFieldAndSend(
                command->getHubIpAddress(),
                command->getAccessKey(),
                task.getId(),
                task.getActionType(),
                task.getActionValue());
        }
        taskVector.clear();

        Utility::sleepMilliseconds(interval);
    }
}


