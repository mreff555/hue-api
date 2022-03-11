#include "deviceContainer.h"

DeviceContainer::DeviceContainer() 
: name("N/A"), description("N/A"), timeStamp(time(nullptr)), instantiationTime(timeStamp)
{

}

std::string DeviceContainer::getName() const
{
    return name;
}

void DeviceContainer::setName(const std::string _name)
{
    name = _name;
}

std::string DeviceContainer::getDescription() const
{

}

void DeviceContainer::setDescription(const std::string _description)
{
    description = _description;
}

Hue::Device DeviceContainer::getData() const
{
    return device;
}

void DeviceContainer::setData(const Hue::Device _device)
{
    device = _device;
}

time_t DeviceContainer::getTimeStamp() const
{
    return timeStamp;
}

void DeviceContainer::setTimeStamp()
{
    timeStamp = time(nullptr);
}