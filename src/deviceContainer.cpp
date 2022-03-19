#include "deviceContainer.h"
#include <sstream>

DeviceContainer::DeviceContainer() 
: name("N/A"), description("N/A"), timeStamp(Utility::currentTimeInMilliseconds()), instantiationTime(timeStamp)
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
    return description;
}

void DeviceContainer::setDescription(const std::string _description)
{
    description = _description;
}

Hue::Device DeviceContainer::getData() const
{
    return device;
}

std::shared_ptr<Hue::Device> DeviceContainer::getDataBuffer()
{
    auto devPtr = std::make_shared<Hue::Device>(device);
    return devPtr;
}

void DeviceContainer::setData(const Hue::Device _device)
{
    device = _device;
}

Utility::milliseconds DeviceContainer::getTimeStamp() const
{
    return timeStamp;
}

void DeviceContainer::setTimeStamp()
{
    timeStamp = Utility::currentTimeInMilliseconds();
}

const std::map<Hue::HueFields, std::string> fieldMap =
{
    // {Hue::STATE_BRI, device.state.bri}
};