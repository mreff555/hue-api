#include "device.h"
#include <iostream>


Hue::Xy::Xy(float _x, float _y) 
{
  SmartField<float> x("abc", "def", _x);
  SmartField<float> y("abc", "def", _y);
  std::cout << "setting x to " << x.getValue() << "\n";
  std::cout << x.getBody() << "\n";

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

Hue::StreamingCapabilities::StreamingCapabilities(bool _renderer, bool _proxy)
: renderer(_renderer), proxy(_proxy)
{

}

Hue:: Capabilities::Capabilities(bool _certified, ControlCapabilities _control, StreamingCapabilities _streaming)
: certified(_certified), control(_control), streaming(_streaming)
{

}

Hue::StartUp::StartUp(std::string _mode, bool _configured)
: mode(_mode), configured(_configured)
{

}

Hue::Config::Config(std::string _archtype, std::string _function, std::string _direction, StartUp _startUp)
: archtype(_archtype), function(_function), direction(_direction), startUp(_startUp)
{

}

Hue::Device::Device(State _state, SwUpdate _swUpdate, std::string _type, std::string _name, std::string _modelid, std::string _manufacturername, std::string _productname, Capabilities _capabilities, Config _config, std::string _uniqueid, std::string _swversion, std::string _swconfigid, std::string _productid)
: state(_state), swupdate(_swUpdate), type(_type), name(_name), modelid(_modelid), manufacturername(_manufacturername), productname(_productname), capabilities(_capabilities), config(_config), uniqueid(_uniqueid), swversion(_swversion), swconfigid(_swconfigid), productid(_productid)
{
    
}
