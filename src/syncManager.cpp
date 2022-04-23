/**
 * @file syncManager.cpp
 * @author your name (feerstd@gmail.com)
 * @brief The purpose of syncManager is to add tasks to the task list for the hue-api.
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "syncManager.h"
#include "timeUtil.h"

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
        std::string ip = command->getHubIpAddress();
        std::string key = command->getAccessKey();
        while(taskQueue.size())
        {
            command->setFieldAndSend(
                ip,
                key,
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
