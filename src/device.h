#ifndef DEVICE_H
#define DEVICE_H

#include <string>

namespace Hue
{
    struct Xy
    {
        float x;
        float y;
        Xy(float, float);
        Xy(){}
        ~Xy() = default;
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
        State(bool, unsigned, unsigned, unsigned, std::string, Xy, unsigned, std::string, std::string, std::string, bool);
        State(){}
        ~State() = default;
    };

    struct SwUpdate
    {
        std::string state;
        std::string lastInstall;
        SwUpdate(std::string, std::string);
        SwUpdate(){}
        ~SwUpdate() = default;
    };

    struct Ct
    {
        unsigned min;
        unsigned max;
        Ct(unsigned, unsigned);
        Ct(){}
        ~Ct() = default;
    };

    struct ControlCapabilities
    {
        unsigned mindimlevel;
        unsigned maxlumen;
        std::string colorgamuttype;
        float colorgamut[3][2];
        Ct ct;
        ControlCapabilities(unsigned, unsigned, std::string, float[3][2], Ct);
        ControlCapabilities(){}
        ~ControlCapabilities() = default;
    };

    struct StreamingCapabilities
    {
        bool renderer;
        bool proxy;
        StreamingCapabilities(bool, bool);
        StreamingCapabilities(){}
        ~StreamingCapabilities() = default;
    };

    struct Capabilities
    {
        bool certified;
        ControlCapabilities control;
        StreamingCapabilities streaming;
        Capabilities(bool, ControlCapabilities, StreamingCapabilities);
        Capabilities(){}
        ~Capabilities() = default;
    };

    struct StartUp
    {
        std::string mode;
        bool configured;
        StartUp(std::string, bool);
        StartUp(){}
        ~StartUp() = default;
    };

    struct Config
    {
        std::string archtype;
        std::string function;
        std::string direction;
        StartUp startUp;
        Config(std::string, std::string, std::string, StartUp);
        Config(){}
        ~Config() = default;
    };

    struct Device
    {
        State state;
        SwUpdate swupdate;
        std::string type;
        std::string name;
        std::string modelid;
        std::string manufacturername;
        std::string productname;
        Capabilities capabilities;
        Config config;
        std::string uniqueid;
        std::string swversion;
        std::string swconfigid;
        std::string productid;
        Device(
            State, 
            SwUpdate, 
            std::string, 
            std::string, 
            std::string, 
            std::string, 
            std::string, 
            Capabilities, 
            Config, 
            std::string, 
            std::string, 
            std::string, 
            std::string);
        Device(){}
        ~Device() = default;
    };
}
#endif /* DEVICE_H */