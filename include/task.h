#ifndef TASK_H
#define TASK_H

#include "deviceContainer.h"
#include <cstdint>

union Value
{
    double floatingPoint;

    int64_t integer;
};

union Rate
{
    double floatingPoint;

    int64_t integer;
};

class Task : public DeviceContainer
{
    public:
    Task(const unsigned short);

    Task(const unsigned short, const Value, const Rate);

    virtual ~Task() = default;

    unsigned short getId() const;

    private:
    const unsigned short id;

    Value value;

    Rate rate;

    void* field;
};

#endif  /* TASK_H */