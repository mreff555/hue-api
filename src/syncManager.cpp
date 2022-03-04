#include "syncManager.h"
#include "smartField.h"

SyncManager::SyncManager(std::shared_ptr<Command>(_command), std::shared_ptr<Hue::Device>(_deviceState)) 
: command(_command), deviceState(_deviceState)
{

}

void SyncManager::runEventLoop(bool &terminate)
{
    // deviceState->state.xy.x.getBody();
}


