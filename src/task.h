#ifndef TASK_H
#define TASK_H

#include "deviceContainer.h"
#include <string>
#include <cstdint>

class Task : public DeviceContainer
{
    public:
    Task(const Hue::HueFieldEnum, const unsigned short, const std::string);

    virtual ~Task() = default;

    unsigned short getId() const;

    Hue::HueFieldEnum getActionType() const;

    std::string getActionValue() const;

    private:
    const Hue::HueFieldEnum actionTypeEnum;

    const unsigned short id;

    const std::string value;
};

#endif  /* TASK_H */