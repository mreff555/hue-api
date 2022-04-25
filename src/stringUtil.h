#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>
#include <sstream>

namespace Utility
{

    bool is_number(const std::string& s);

    /**
    * @brief Converts a integer or floating point value to a string using the specified precision
    * @param value the numeric value
    * @param n number of decimal places
    * @return String representation of value
    */
    template <typename T>
    std::string to_string_with_precision(const T value, const int n = 5) {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << value;
        return out.str();
    }

    /**
    * @brief Compares two strings, ignoring case
    * @param str1 an l-value string
    * @param str2 a l-value or r-value string
    * @return True if the strings match
    */
    bool caseInSensStringCompare(std::string &str1, std::string &str2);

    /**
    * @brief Compares two strings, ignoring case
    * @param str1 a l-value string
    * @param str2 a l-value or r-value string
    * @return True if the strings match
    */
    bool caseInSensStringCompare(std::string &str1, std::string &&str2);
}

#endif /* STRING_UTIL_H_ */