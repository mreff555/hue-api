#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <map>

namespace Hue
{
    struct State
    {
        bool on;
        unsigned bri;
        unsigned hue;
        unsigned sat;
        std::string effect;
        float xy[2];
        unsigned ct;
        std::string alert;
        std::string colormode;
        std::string mode;
        bool reachable;
        State(
            bool _on, 
            unsigned _bri, 
            unsigned _hue, 
            unsigned _sat, 
            std::string _effect, 
            float _xy[2], 
            unsigned _ct, 
            std::string _alert, 
            std::string _colormode, 
            std::string _mode, 
            bool _reachable);
        State();
        ~State() = default;
    };

    struct SwUpdate
    {
        std::string state;
        std::string lastInstall;
        SwUpdate(std::string _state, std::string _lastInstall);
        SwUpdate();
        ~SwUpdate() = default;
    };

    struct Ct
    {
        unsigned min;
        unsigned max;
        Ct(unsigned _min, unsigned _max);
        Ct();
        ~Ct() = default;
    };

    struct ControlCapabilities
    {
        unsigned mindimlevel;
        unsigned maxlumen;
        std::string colorgamuttype;
        float colorgamut[3][2];
        Ct ct;
        ControlCapabilities(
            unsigned _mindimlevel,
            unsigned _maxlumen,
            std::string _colorgamuttype,
            float _colorgamut[3][2],
            Ct _ct);
        ControlCapabilities();
        ~ControlCapabilities() = default;
    };

    struct StreamingCapabilities
    {
        bool renderer;
        bool proxy;
        StreamingCapabilities(bool _renderer, bool _proxy);
        StreamingCapabilities();
        ~StreamingCapabilities() = default;
    };

    struct Capabilities
    {
        bool certified;
        ControlCapabilities control;
        StreamingCapabilities streaming;
        Capabilities(
            bool _certified,
            ControlCapabilities _control,
            StreamingCapabilities _streaming);
        Capabilities();
        ~Capabilities() = default;
    };

    struct StartUp
    {
        std::string mode;
        bool configured;
        StartUp(std::string _mode, bool _configured);
        StartUp();
        ~StartUp() = default;
    };

    struct Config
    {
        std::string archtype;
        std::string function;
        std::string direction;
        StartUp startUp;
        Config(
            std::string _archtype, 
            std::string _function,
            std::string _direction,
            StartUp _startUp);
        Config();
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
            State _state, 
            SwUpdate _swupdate, 
            std::string _type, 
            std::string _name, 
            std::string _modelid, 
            std::string _manufacturername, 
            std::string _productname, 
            Capabilities _capabilities, 
            Config _config, 
            std::string _uniqueid, 
            std::string _swversion, 
            std::string _swconfigid, 
            std::string _productid);
        Device();
        ~Device() = default;
        void initializeFieldMaps();
    };

    enum HueFieldEnum
    {
        STATE_ON,
        STATE_BRI,
        STATE_HUE,
        STATE_SAT,
        STATE_XY,
        STATE_EFFECT,
        STATE_CT,
        STATE_COLORMODE,
        STATE_REACHABLE,
        SWUPDATE_STATE,
        SWUPDATE_INSTALL,
        TYPE,
        NAME,
        MODELID,
        MANUFACTURERNAME,
        PRODUCTNAME,
        CAPABILITIES_CERTIFIED,
        CAPABILITIES_CONTROL_MINDIMLEVEL,
        CAPABILITIES_CONTROL_MAXLUMEN,
        CAPABILITIES_CONTROL_COLORGAMUTTYPE,
        CAPABILITIES_CONTROL_COLORGAMUT,
        CAPABILITIES_CONTROL_CT_MIN,
        CAPABILITIES_CONTROL_CT_MAX,
        CAPABILITIES_STREAMING_RENDER,
        CAPABILITIES_STREAMING_PROXY,
        CONFIG_ARCHTYPE,
        CONFIG_FUNCTION,
        CONFIG_DIRECTION,
        CONFIG_STARTUP_MODE,
        CONFIG_STARTUP_CONFIGURED,
        UNIQUEID,
        SWVERSION,
        SWCONFIGID,
        PRODUCTID
    };

    struct FieldStruct
    {
        std::string category;
        std::string fieldName;
        std::string body;
    };

    typedef std::map<HueFieldEnum, FieldStruct> FieldMap;
}
#endif /* DEVICE_H */
