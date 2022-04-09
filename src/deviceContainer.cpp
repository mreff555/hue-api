#include "deviceContainer.h"
#include "stringUtil.h"
#include <iostream>

using namespace Hue;

DeviceContainer::DeviceContainer() 
: name("N/A"), description("N/A"), id(-1), timeStamp(Utility::currentTimeInMilliseconds()), instantiationTime(timeStamp), 
fieldMap({
    {STATE_ON, {"state", "on", "false"}},        
    {STATE_BRI, {"state", "bri", "false"}},
    {STATE_HUE, {"state", "hue", "false"}},
    {STATE_SAT, {"state", "sat", "false"}},
    {STATE_XY, {"state", "xy", "[0,0]"}},
    {STATE_EFFECT, {"state", "effect", "false"}},
    {STATE_CT, {"state", "ct", "false"}},
    {STATE_COLORMODE, {"state", "colormode", "false"}},
    {STATE_REACHABLE, {"state", "reachable", "false"}},
    {SWUPDATE_STATE, {"swupdate", "state", ""}},
    {SWUPDATE_INSTALL, {"swupdate", "install", ""}},
    {TYPE, {"", "type", ""}},
    {NAME, {"", "name", ""}},
    {MODELID, {"", "", ""}},
    {MANUFACTURERNAME, {"", "manufacturername", ""}},
    {PRODUCTNAME, {"", "productname", ""}},
    {CAPABILITIES_CERTIFIED, {"", "", ""}},
    {CAPABILITIES_CONTROL_MINDIMLEVEL, {"", "", ""}},
    {CAPABILITIES_CONTROL_MAXLUMEN, {"", "", ""}},
    {CAPABILITIES_CONTROL_COLORGAMUTTYPE, {"", "", ""}},
    {CAPABILITIES_CONTROL_COLORGAMUT, {"", "", ""}},
    {CAPABILITIES_CONTROL_CT_MIN, {"", "", ""}},
    {CAPABILITIES_CONTROL_CT_MAX, {"", "", ""}},
    {CAPABILITIES_STREAMING_RENDER, {"", "", ""}},
    {CAPABILITIES_STREAMING_PROXY , {"", "", ""}},
    {CONFIG_ARCHTYPE, {"", "", ""}},
    {CONFIG_FUNCTION, {"", "", ""}},
    {CONFIG_DIRECTION, {"", "", ""}},
    {CONFIG_STARTUP_MODE, {"", "", ""}},
    {CONFIG_STARTUP_CONFIGURED, {"", "", ""}},
    {UNIQUEID, {"", "uniqueid", ""}},
    {SWVERSION, {"", "swversion", ""}},
    {SWCONFIGID, {"", "swconfigid", ""}},
    {PRODUCTID, {"", "productid", ""}},
})
{
    setTimeStamp();
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
    if(_value != "true" 
        && _value != "false" 
        && !Utility::is_number(_value)
        && _value.find('['))
    {
        bodyValue << "\"" << _value << "\"";
        _value = bodyValue.str();
    }

    std::stringstream body;
    body << "{\"" << fieldMap.at(_field).fieldName << "\":" << _value << "}";
    return body.str();
}