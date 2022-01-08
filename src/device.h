#ifndef DEVICE_H
#define DEVICE_H

#include <string>

struct Xy
{
    float x;
    float y;
};

struct State
{
    bool on;
    unsigned bri;
    unsigned hue;
    unsigned sat;
    std::string effect;
    Xy xy;
    unsigned ct;
    std::string alert;
    std::string colormode;
    std::string mode;
    bool reachable;
};

struct SwUpdate
{
    std::string state;
    std::string lastinstall;
};

struct Ct
{
    unsigned min;
    unsigned max;
};

struct ControlCapabilities
{
    unsigned mindimlevel;
    unsigned maxlumen;
    std::string colorgamuttype;
    float colorgamut[3][2];
    Ct ct;
};

struct StreamingCapabilities
{
    bool render;
    bool proxy;
};

struct Capabilities
{
    std::string certified;
    ControlCapabilities control;
    StreamingCapabilities streaming;
};

struct StartUp
{
    std::string mode;
    bool configured;
};

struct config
{
    std::string archtype;
    std::string function;
    std::string direction;
    Startup startup;
};

struct Device
{
    State state;
    SwUpdate swupdate
    std::string type;
    std::string name;
    std::string modelid;
    std::string manufacturername;
    std::string productname;
    Capibilities capibilities;
    Config config;
    std::string uniqueid;
    std::string swversion;
    std::string swconfigid;
    std::string productid;
};

#endif /* DEVICE_H */