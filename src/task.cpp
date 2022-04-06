#include "task.h"

// Task::Task(const unsigned short _id) : id(_id) {} 


Task::Task(
    const Hue::HueFieldEnum _typeEnum, 
    const unsigned short _id, 
    const std::string _value)
: typeEnum(_typeEnum), 
id(_id), 
value(_value)
{
    auto data = getDataBuffer();    
}

unsigned short Task::getId() const
{
    return id;
}
