#ifndef SMART_FIELD_H
#define SMART_FIELD_H

#include <string>
#include <ctime>

namespace Hue
{
    template<class T>
    class SmartField
    {
        T value;
        time_t timeStamp;
        std::string url;
        std::string body;

        public:
        void setValue(T _value)
        {
            this->value = _value;
        }

        T getValue() const
        {
            return this->value;
        }
        
        inline void updateTimeStamp()
        {
            this->timeStamp = time(nullptr);
        }
        
        time_t getTimeStamp() const
        {
            return this->timeStamp; 
        }
        
        std::string getUrl() const
        {
            return this->url;
        }
        
        std::string getBody() const
        {
            return this->body;
        }
        
        inline SmartField(std::string _url, std::string _body) 
        : url(_url), body(_body)
        {
            this->updateTimeStamp();
        }
        
        virtual ~SmartField() = default;
    };
}

#endif /* SMART_FIELD_H */