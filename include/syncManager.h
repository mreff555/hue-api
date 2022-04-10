/**
 * @file syncManager.h
 * @author Dan Feerst (feerstd@gmail.com.com)
 * @brief The Sync Manager is responsible for updating the database,
 * executing tasks and adding additional tasks.
 * 
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SYNC_MANAGER_H
#define SYNC_MANAGER_H

#include "config.h"
#include "command.h"
#include "device.h"
#include "timeUtil.h"
#include "task.h"
#include <queue>

constexpr Utility::milliseconds interval = 250;

class SyncManager
{
    public:
    SyncManager(std::shared_ptr<Command>, std::shared_ptr<Hue::Device>);

    virtual ~SyncManager() = default;

    /**
     * @brief A 4Hz event loops which runs until the terminate flag is set.  Each
     * cycle, outdated entries in the memory database are updated and tasks are 
     * removed from the vector and executed.
     *
     * @todo It seems like there may be some type of unknown limit on the rate
     * that the HUE hub is capible of setting commands.  At some point I will
     * likely have to limit the number of tasks that can be execuated within
     * one cycle.
     * 
     * @param terminate loop will terminate when true
     */
    void runEventLoop(bool &terminate);

    void addTask(const Task &_task);

    private:
    std::shared_ptr<Command> command;
    std::shared_ptr<Hue::Device> deviceState;
    std::queue<Task> taskQueue;
    std::queue<Task> tempTaskQueue;
};

#endif /* SYNC_MANAGER_H */