#include "task.h"

Task::Task(
    const Hue::HueFieldEnum _actionTypeEnum, 
    const unsigned short _id, 
    const std::string _value)
: actionTypeEnum(_actionTypeEnum), 
id(_id), 
value(_value)
{
    auto data = getDataBuffer();    
}

unsigned short Task::getId() const
{
    return id;
}

Hue::HueFieldEnum Task::getActionType() const
{
    return actionTypeEnum;
}

std::string Task::getActionValue() const
{
    return value;
}
