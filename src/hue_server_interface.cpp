#include "hue_server_interface.h"
#include "task.h"
#include <string>

HueServerInterface::HueServerInterface(std::shared_ptr<SyncManager> _syncManager) : syncManager(_syncManager){}

void HueServerInterface::setLightOn(const unsigned short _lightId, bool _on)
{
    std::string outboundValue =  _on ? std::string("true") : std::string("false");
    if(_lightId < deviceArraySize)
    {
        const Task task(Hue::STATE_ON, _lightId, outboundValue);
        
    }
}

bool HueServerInterface::setLightBrightness(const unsigned short _lightId, const unsigned short _value)
{
    // bool returnValue = false;
    // std::string outboundValue = (_value <= 254) ? std::to_string(_value) : "INVALID";
    // if(outboundValue != "INVALID")
    // {
    //     setFieldAndSend(
    //         mCfg->getInternalIpAddress(), 
    //         mCfg->getKey(), 
    //         _lightId, 
    //         Hue::STATE_BRI,
    //         outboundValue);
    //     returnValue = true;  
    // }
    // return returnValue;
}

bool HueServerInterface::setLightHue(const unsigned short _lightId, const unsigned short _value)
{
    // bool returnValue = false;
    // std::string outboundValue = (_value <= 65535) ? std::to_string(_value) : "INVALID";
    // if(outboundValue != "INVALID")
    // {
    //     setFieldAndSend(
    //         mCfg->getInternalIpAddress(), 
    //         mCfg->getKey(), 
    //         _lightId, 
    //         Hue::STATE_HUE,
    //         outboundValue);
    //     returnValue = true;  
    // }
    // return returnValue;
}

bool HueServerInterface::setLightSaturation(const unsigned short _lightId, const unsigned short _value)
{
    // bool returnValue = false;
    // std::string outboundValue = (_value <= 254) ? std::to_string(_value) : "INVALID";
    // if(outboundValue != "INVALID")
    // {
    //     setFieldAndSend(
    //         mCfg->getInternalIpAddress(), 
    //         mCfg->getKey(), 
    //         _lightId, 
    //         Hue::STATE_BRI,
    //         outboundValue);
    //     returnValue = true;  
    // }
    // return returnValue;
}

bool HueServerInterface::setLightColorXY(const unsigned short _lightId, const float _x, float _y)
{
    // bool returnValue = false;
    // std::string outboundX = (_x <= 1) ? Utility::to_string_with_precision(_x, 4) : "INVALID";
    // std::string outboundY = (_y <= 1) ? Utility::to_string_with_precision(_y, 4) : "INVALID";
    // std::stringstream ss;
    // ss << "["  << outboundX << "," << outboundY << "]";
    // if((outboundX != "INVALID") && (outboundY != "INVALID"))
    // {
    //     setFieldAndSend(
    //         mCfg->getInternalIpAddress(), 
    //         mCfg->getKey(), 
    //         _lightId, 
    //         Hue::STATE_XY,
    //         ss.str());

    //     returnValue = true;  
    // }
    // return returnValue;
}