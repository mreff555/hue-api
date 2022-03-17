#include "task.h"

Task::Task(const unsigned short _id) : id(_id) {} 


Task::Task(const unsigned short _id, const Value _value, const Rate _rate)
: id(_id), value(_value), rate(_rate)
{
    auto data = getDataBuffer();    
}

unsigned short Task::getId() const
{
    return id;
}
