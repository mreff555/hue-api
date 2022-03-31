#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include <string>

namespace Utility {

    typedef uint64_t seconds;
    typedef uint64_t milliseconds;
    typedef uint64_t millisecondSinceEpoch;

    /**
     * @brief The number of millisecond since the epoc in ZULU time.
     *
     * @return millisecondSinceEpoch
     */
    millisecondSinceEpoch currentTimeInMilliseconds();

    /**
     * @brief The current time in ISO8601 format at ZULU time.
     *
     * @return std::string
     */
    std::string currentTime();
    /**
     * @brief The current time plus some number of milliseconds in ISO8601 format at ZULU time.
     *
     * @param offset
     * @return std::string
     */
    std::string currentTimePlusOffset(milliseconds);
    /**
     * @brief Format the number of milliseconds since the epoch (1970) as ISO8601 format at ZULU time.
     *
     * @param time
     * @return std::string
     */
    std::string formatMillisecondsSinceEpoch(millisecondSinceEpoch);

    /**
     * @brief 
     * 
     */
    void sleepSeconds(seconds);

    /**
     * @brief 
     * 
     */
    void sleepMilliseconds(milliseconds);
};

#endif //TIME_UTIL_H
