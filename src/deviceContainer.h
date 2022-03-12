#ifndef DEVICE_CONTAINER_H
#define DEVICE_CONTAINER_H

#include "device.h"
#include "timeUtil.h"
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

    Utility::millisecondSinceEpoch getTimeStamp() const;

    void setTimeStamp();

    private:
    std::string name;

    std::string description;

    Hue::Device device;

    Utility::millisecondSinceEpoch timeStamp;

    const Utility::millisecondSinceEpoch instantiationTime;
};

#endif /* DEVICE_CONTAINER_H */