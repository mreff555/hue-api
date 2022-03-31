#ifndef DEVICE_CONTAINER_H
#define DEVICE_CONTAINER_H

#include "device.h"
#include "timeUtil.h"
#include <string>
#include <memory>
#include <sstream>

// extern std::map<Hue::HueFields, std::string> FieldMap;

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

    void setId(short);

    short getId() const;

    Utility::millisecondSinceEpoch getTimeStamp() const;
    
    void setTimeStamp();

    std::string getCategoryStringFromHueEnum(Hue::HueFieldEnum _field) const;

    std::string getFieldStringFromHueEnum(Hue::HueFieldEnum) const;

    std::string getBodyStringFromHueEnum(Hue::HueFieldEnum, std::string) const;

    protected:
    template<typename valueT>
    bool setDeviceField(Hue::HueFieldEnum, valueT);

    std::string name;

    std::string description;

    Hue::Device device;

    private:
    short id;

    Utility::millisecondSinceEpoch timeStamp;

    const Utility::millisecondSinceEpoch instantiationTime;

    Hue::FieldMap fieldMap;
};

#endif /* DEVICE_CONTAINER_H */