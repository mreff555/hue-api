#ifndef SMART_FIELD_H
#define SMART_FIELD_H

#include <string>
#include <ctime>

template<class T>
class SmartField
{
    public:
    
    SmartField(std::string, std::string);

    SmartField(std::string, std::string, T);

    void operator()(const T&);
    
    void setValue(T);

    T getValue() const;
    
    inline void updateTimeStamp();
    
    time_t getTimeStamp() const;
    
    std::string getUrl() const;
    
    std::string getBody() const;
    
    virtual ~SmartField() = default;
    
    private:
    T value;
    time_t timeStamp;
    std::string url;
    std::string body;
};
#endif /* SMART_FIELD_H */
