#include "timeUtil.h"
#include <chrono>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <thread>


namespace Utility {

    /**
     * @brief The number of millisecond since the epoch in ZULU time.
     *
     * @return millisecondSinceEpoch
     */
    millisecondSinceEpoch currentTimeInMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    /**
     * @brief The current time in ISO8601 format at ZULU time.
     *
     * @return std::string
     */
    std::string currentTime()
    {
        return formatMillisecondsSinceEpoch(currentTimeInMilliseconds());
    }

    /**
     * @brief The current time plus some number of milliseconds in ISO8601 format at ZULU time.
     *
     * @param offset
     * @return std::string
     */
    std::string currentTimePlusOffset(milliseconds _offset)
    {
        return formatMillisecondsSinceEpoch(currentTimeInMilliseconds() + _offset);
    }


    /**
     * @brief Format the number of milliseconds since the epoch (1970) as ISO8601 format at ZULU time.
     *
     * @param time
     * @return std::string
     */
    std::string formatMillisecondsSinceEpoch(millisecondSinceEpoch _time)
    {
        boost::posix_time::ptime tmp = boost::posix_time::from_time_t(
            _time / 1000) + boost::posix_time::millisec(_time % 1000);
        std::string tmpS = boost::posix_time::to_iso_extended_string(tmp);
        return tmpS.substr(0, 23)
                + ((tmpS.size() < 23) ? ".000" : "")
                + "Z";
    }
  
    /**
     * @brief 
     * 
     */
    void sleepSeconds(seconds _seconds)
    {
        std::this_thread::sleep_for(std::chrono::seconds(_seconds));
    }

    /**
     * @brief 
     * 
     */
    void sleepMilliseconds(milliseconds _milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(_milliseconds));
    }
}
