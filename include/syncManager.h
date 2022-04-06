#ifndef SYNC_MANAGER_H
#define SYNC_MANAGER_H

#include "config.h"
#include "command.h"
#include "device.h"
#include "timeUtil.h"
#include "task.h"
#include <vector>

constexpr Utility::milliseconds interval = 250;

class SyncManager
{
    public:
    SyncManager(std::shared_ptr<Command>, std::shared_ptr<Hue::Device>);

    virtual ~SyncManager() = default;

    void runEventLoop(bool&);
    
    private:
    std::shared_ptr<Command> command;
    std::shared_ptr<Hue::Device> deviceState;

    std::vector<Task> taskVector;
};

#endif /* SYNC_MANAGER_H */