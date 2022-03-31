#include "deviceContainer.h"
#include "stringUtil.h"

using namespace Hue;

DeviceContainer::DeviceContainer() 
: name("N/A"), description("N/A"), id(-1), timeStamp(Utility::currentTimeInMilliseconds()), instantiationTime(timeStamp), 
fieldMap({
    {STATE_ON, {"state", "on", "false"}},        
    {STATE_BRI, {"state", "bri", "false"}},
    {STATE_HUE, {"state", "hue", "false"}},
    {STATE_SAT, {"state", "sat", "false"}},
    {STATE_XY_X, {"state", "xy.x", "false"}},
    {STATE_XY_Y, {"state", "xy.y", "false"}},
    {STATE_EFFECT, {"state", "effect", "false"}},
    {STATE_CT, {"state", "ct", "false"}},
    {STATE_COLORMODE, {"state", "colormode", "false"}},
    {STATE_REACHABLE, {"state", "reachable", "false"}}
}) {}

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

void DeviceContainer::setId(short _id)
{
    id = _id;
}

short DeviceContainer::getId() const
{
    return id;
}

Utility::milliseconds DeviceContainer::getTimeStamp() const
{
    return timeStamp;
}

void DeviceContainer::setTimeStamp()
{
    timeStamp = Utility::currentTimeInMilliseconds();
}

std::string DeviceContainer::getCategoryStringFromHueEnum(Hue::HueFieldEnum _field) const
{
    return fieldMap.at(_field).category;
}

std::string DeviceContainer::getFieldStringFromHueEnum(Hue::HueFieldEnum _field) const
{
    return fieldMap.at(_field).fieldName;
}

std::string DeviceContainer::getBodyStringFromHueEnum(Hue::HueFieldEnum _field, std::string _value) const
{
    // TODO: Definately need more some error checking here.
    std::stringstream bodyValue;
    if(_value != "true" && _value != "false" && !Utility::is_number(_value))
    {
        bodyValue << "\"" << _value << "\"";
        _value = bodyValue.str();
    }

    std::stringstream body;
    body << "{\"" << fieldMap.at(_field).fieldName << "\":" << _value << "}";
    return body.str();
}

template<typename valueT>
bool DeviceContainer::setDeviceField(Hue::HueFieldEnum _field, valueT _value)
{
    // std::cout << fieldMap[_field].catagory << "\n";
    //std::stringstream ss;
    //ss << "{\"" << fieldMap[_field].catagory << "\":\"" <<  std::to_string(_value) << "\"}"
    //fieldMap[_field].body = 
}