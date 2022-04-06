#ifndef TASK_H
#define TASK_H

#include "deviceContainer.h"
#include <string>
#include <cstdint>

class Task : public DeviceContainer
{
    public:
    // Task(const unsigned short);

    Task(const Hue::HueFieldEnum, const unsigned short, const std::string);

    virtual ~Task() = default;

    unsigned short getId() const;

    private:
    const Hue::HueFieldEnum typeEnum;

    const unsigned short id;

    const std::string value;

    void* field;
};

#endif  /* TASK_H */