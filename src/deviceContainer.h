#ifndef DEVICE_CONTAINER_H
#define DEVICE_CONTAINER_H

#include "device.h"
#include "timeUtil.h"
#include <string>
#include <map>
#include <memory>

extern std::map<Hue::HueFields, int> FieldMap;

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

    std::shared_ptr<Hue::Device> getDataBuffer();

    void setData(const Hue::Device);

    Utility::millisecondSinceEpoch getTimeStamp() const;

    void setTimeStamp();

    protected:
    std::string name;

    std::string description;

    Hue::Device device;

    private:
    Utility::millisecondSinceEpoch timeStamp;

    const Utility::millisecondSinceEpoch instantiationTime;
};

#endif /* DEVICE_CONTAINER_H */