#include "deviceContainer.h"
#include <util/stringUtil.h>
#include "task.h"
#include <iostream>

using namespace Hue;

DeviceContainer::DeviceContainer() 
: name("N/A"),
description("N/A"),
id(-1),
timeStamp(Utility::currentTimeInMilliseconds()),
instantiationTime(timeStamp),
fieldMap({
    {STATE_ON,                              {"state", "on", "false", BOOL, false, false, true, {}}},        
    {STATE_BRI,                             {"state", "bri", "0", INT32, false, 1, 254, {}}},
    {STATE_HUE,                             {"state", "hue", "0", INT32, false, 0, 65535, {}}},
    {STATE_SAT,                             {"state", "sat", "0", INT32, false, 0, 254, {}}},
    {STATE_XY,                              {"state", "xy", "[0,0]", FLOAT, false, 0, 1, {}}},
    {STATE_EFFECT,                          {"state", "effect", "false", STRING, false, 4, 10, {"none", "colorloop"}}},
    {STATE_CT,                              {"state", "ct", "false", INT32, false, 153, 500, {}}},
    {STATE_COLORMODE,                       {"state", "colormode", "false", INT32, false, 0, 254, {}}},
    {STATE_REACHABLE,                       {"state", "reachable", "false", INT32, false, 0, 254, {}}},
    {SWUPDATE_STATE,                        {"swupdate", "state", "", INT32, false, 0, 254, {}}},
    {SWUPDATE_INSTALL,                      {"swupdate", "install", "", INT32, false, 0, 254, {}}},
    {TYPE,                                  {"", "type", "", INT32, false, 0, 254, {}}},
    {NAME,                                  {"", "name", "", INT32, false, 0, 254, {}}},
    {MODELID,                               {"", "", "", INT32, false, 0, 254, {}}},
    {MANUFACTURERNAME,                      {"", "manufacturername", "", INT32, false, 0, 254, {}}},
    {PRODUCTNAME,                           {"", "productname", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_CERTIFIED,                {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_CONTROL_MINDIMLEVEL,      {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_CONTROL_MAXLUMEN,         {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_CONTROL_COLORGAMUTTYPE,   {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_CONTROL_COLORGAMUT,       {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_CONTROL_CT_MIN,           {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_CONTROL_CT_MAX,           {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_STREAMING_RENDER,         {"", "", "", INT32, false, 0, 254, {}}},
    {CAPABILITIES_STREAMING_PROXY ,         {"", "", "", INT32, false, 0, 254, {}}},
    {CONFIG_ARCHTYPE,                       {"", "", "", INT32, false, 0, 254, {}}},
    {CONFIG_FUNCTION,                       {"", "", "", INT32, false, 0, 254, {}}},
    {CONFIG_DIRECTION,                      {"", "", "", INT32, false, 0, 254, {}}},
    {CONFIG_STARTUP_MODE,                   {"", "", "", INT32, false, 0, 254, {}}},
    {CONFIG_STARTUP_CONFIGURED,             {"", "", "", INT32, false, 0, 254, {}}},
    {UNIQUEID,                              {"", "uniqueid", "", INT32, false, 0, 254, {}}},
    {SWVERSION,                             {"", "swversion", "", INT32, false, 0, 254, {}}},
    {SWCONFIGID,                            {"", "swconfigid", "", INT32, false, 0, 254, {}}},
    {PRODUCTID,                             {"", "productid", "", INT32, false, 0, 254, {}}},
})
{
    setTimeStamp();
}

bool DeviceContainer::validate(const Task &task)
{
    bool valid = false;

    switch(task.getActionType())
    {
        case STATE_ON:
            
        break;

        case STATE_BRI:

        break;

    }
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
    // TODO: Need more some error checking here.
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