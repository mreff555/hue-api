#include "device.h"

Hue::Xy::Xy(float x, float y) 
{
    
}

Hue::State::State(bool on, unsigned bri, unsigned hue, unsigned set, std::string effict, Xy xy, unsigned ct, std::string alert, std::string colormode, std::string mode, bool reachable)
{

}

Hue::SwUpdate::SwUpdate(std::string state, std::string lastInstall) 
{

}

Hue::Ct::Ct(unsigned min, unsigned max)
{

}

Hue::ControlCapabilities::ControlCapabilities(unsigned mindimlevel, unsigned maxlumen, std::string colorgamuttype, float colorgamut[3][2], Ct ct)
{

}

Hue::StreamingCapabilities::StreamingCapabilities(bool render, bool proxy)
{

}

Hue:: Capabilities::Capabilities(std::string certified, ControlCapabilities control, StreamingCapabilities streaming)
{

}

Hue::StartUp::StartUp(std::string mode, bool configured)
{

}

Hue::Config::Config(std::string archtype, std::string function, std::string direction, StartUp startUp)
{

}

Hue::Device::Device(State state, SwUpdate swupdate, std::string type, std::string name, std::string modelid, std::string manufacturername, std::string productname, Capabilities capabilities, Config config, std::string uniqueid, std::string swversion, std::string swconfigid, std::string productid)
{
    
}