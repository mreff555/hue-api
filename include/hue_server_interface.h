/**
 * @file hue_server_interface.h
 * @author Dan Feerst (feerstd@gmail.com)
 * @brief This is the console interface for the hue_server
 * @version 0.1
 * @date 2022-04-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HUE_SERVER_INTERFACE_H
#define HUE_SERVER_INTERFACE_H

#include "syncManager.h"
#include <memory>

//namespace Hue
class HueServerInterface
{
    public:
    HueServerInterface(std::shared_ptr<SyncManager> _syncManager);

    virtual ~HueServerInterface() = default;

    /**
    * @brief Turn the specified light on/off
    * 
    * @param _lightId value representing a light RANGE [0 - 63]
    * @param _on [DEFAULT = true]
    */
    void setLightOn(const unsigned short _lightId, bool _on = true);

    /**
     * @brief Set the brightness for the specified light
     * 
     * @param _lightId 
     * @param _value positive integer RANGE [0 - 254]
     * 
     * @return true on success
     */
    bool setLightBrightness(const unsigned short _lightId, const unsigned short _value);

    /**
     * @brief Set the hue for the specified light
     * 
     * @param _lightId 
     * @param _value positive integer RANGE [0 - 65535]
     * 
     * @return true on success
     */
    bool setLightHue(const unsigned short _lightId, const unsigned short _value);

    /**
     * @brief Set the saturation for the specified light
     * 
     * @param _lightId 
     * @param _value positive integer RANGE [0 - 254]
     * 
     * @return true on success
     */
    bool setLightSaturation(const unsigned short _lightId, const unsigned short _value);

    /**
     * @brief Set the color for the specified light by X/Y coordinates
     * 
     * @param _lightId 
     * @param _x RANGE [0 - 1]
     * @param _y RANGE [0 - 1]
     * 
     * @return true on success
     */
    bool setLightColorXY(const unsigned short _lightId, const float _x, float _y);

    private:
    std::shared_ptr<SyncManager> syncManager;
};

#endif /* HUE_SERVER_INTERFACE_H */