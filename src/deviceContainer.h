#ifndef DEVICE_CONTAINER_H
#define DEVICE_CONTAINER_H

#include "device.h"
#include <ctime>
#include <string>

class DeviceContainer
{
    public:
    DeviceContainer();

    virtual ~DeviceContainer() = default;

    std::string getName() const;

    void setName(const std::string);

    std::string getDescription() const;

    void setDescription(const std::string);

    Hue::Device getData() const;

    void setData(const Hue::Device);

    time_t getTimeStamp() const;

    void setTimeStamp();

    private:
    std::string name;

    std::string description;

    Hue::Device device;

    time_t timeStamp;

    const time_t instantiationTime;
};

#endif /* DEVICE_CONTAINER_H */