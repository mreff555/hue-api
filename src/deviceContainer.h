/**
 * @file deviceContainer.h
 * @author Dan Feerst (feerstd@gmail.com)
 * @brief The device container provides getters and setters for a
 * device as well as time stamping, identification, and  external description.
 * 
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DEVICE_CONTAINER_H
#define DEVICE_CONTAINER_H

#include <hue/device.h>
#include <util/timeUtil.h>
#include <string>
#include <memory>
#include <sstream>

class Task;

class DeviceContainer
{
    public:
    DeviceContainer();

    virtual ~DeviceContainer() = default;

    bool validate(const Task&);

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