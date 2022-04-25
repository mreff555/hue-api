#include "stringUtil.h"
#include <cctype>
#include <iomanip>

namespace Utility
{
    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), 
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
       
    bool caseInSensStringCompare(std::string &str1, std::string &str2)
    {
        return ((str1.size() ==
            str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](char & c1, char & c2){
                return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
            }));
    }

    bool caseInSensStringCompare(std::string &str1, std::string &&str2)
    {
        return ((str1.size() ==
            str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](char & c1, char & c2){
                return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
            }));
    }

}