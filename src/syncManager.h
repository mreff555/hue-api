#ifndef SYNC_MANAGER_H
#define SYNC_MANAGER_H

#include "command.h"
#include "device.h"

constexpr unsigned short interval = 5;  // Seconds

class SyncManager
{
    public:
    SyncManager(std::shared_ptr<Command>, std::shared_ptr<Hue::Device>);

    virtual ~SyncManager() = default;

    void runEventLoop(bool&);
    
    private:
    std::shared_ptr<Command> command;
    std::shared_ptr<Hue::Device> deviceState;
};

#endif /* SYNC_MANAGER_H */