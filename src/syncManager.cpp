#include "syncManager.h"
#include "timeUtil.h"
#include <iostream>

SyncManager::SyncManager(
    std::shared_ptr<Command>(_command), 
    std::shared_ptr<Hue::Device>(_deviceState)) 
: command(_command), 
deviceState(_deviceState) {}

void SyncManager::runEventLoop(bool &terminate)
{
    while(!terminate)
    {
        // refresh device data
        for(int i = 0; i < deviceArraySize; ++i)
        {
            command->refreshDataFromDevice(i);
        }

        // Perform scheduled tasks until the queue is empty
        while(taskQueue.size())
        {
            command->setFieldAndSend(
                command->getHubIpAddress(),
                command->getAccessKey(),
                taskQueue.front().getId(),
                taskQueue.front().getActionType(),
                taskQueue.front().getActionValue());
                taskQueue.pop();
        }

        // Add new tasks in holding to the queue
        taskQueue.swap(tempTaskQueue);

        Utility::sleepMilliseconds(interval);
    }
}

void SyncManager::addTask(const Task &_task)
{
    tempTaskQueue.push(_task);
}
