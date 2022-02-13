#include "device.h"

Hue::Xy::Xy(float _x, float _y) 
: x(_x), y(_y)
{
    
}

Hue::State::State(bool _on, unsigned _bri, unsigned _hue, unsigned _sat, std::string _effect, Xy _xy, unsigned _ct, std::string _alert, std::string _colormode, std::string _mode, bool _reachable)
: on(_on), bri(_bri), hue(_hue), sat(_sat), effect(_effect), xy(_xy), ct(_ct), alert(_alert), colormode(_colormode), mode(_mode), reachable(_reachable)
{

}

Hue::SwUpdate::SwUpdate(std::string _state, std::string _lastInstall)
: state(_state), lastInstall(_lastInstall)
{

}

Hue::Ct::Ct(unsigned _min, unsigned _max)
: min(_min), max(_max)
{

}

Hue::ControlCapabilities::ControlCapabilities(unsigned _mindimlevel, unsigned _maxlumen, std::string _colorgamuttype, float _colorgamut[3][2], Ct _ct)
: mindimlevel(_mindimlevel), maxlumen(_maxlumen), colorgamuttype(_colorgamuttype), ct(_ct)
{
    // TODO: Need to figure out the best way to do this.
    // colorgamut = {
    //     _colorgamut[0][0],
    //     _colorgamut[0][1],
    //     _colorgamut[1][0],
    //     _colorgamut[1][1],
    //     _colorgamut[2][0],
    //     _colorgamut[2][1]
    //     };
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