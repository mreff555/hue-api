#include "smartField.h"

template<class T>
SmartField<T>::SmartField(std::string _url, std::string _body) 
: url(_url), body(_body)
{
    this->updateTimeStamp();
}

template<class T>
SmartField<T>::SmartField(std::string _url, std::string _body, T _value) 
: url(_url), body(_body), value(_value)
{
    this->updateTimeStamp();
}

template<class T>
void SmartField<T>::operator()(const T &obj)
{
    this->setValue(obj);
}

template<class T>
void SmartField<T>::setValue(T _value)
{
    this->value = _value;
    this->updateTimeStamp();
}

template<class T>
T SmartField<T>::getValue() const
{
    return this->value;
}

template<class T>
void SmartField<T>::updateTimeStamp()
{
    this->timeStamp = time(nullptr);
}

template<class T>
time_t SmartField<T>::getTimeStamp() const
{
    return this->timeStamp; 
}

template<class T>
std::string SmartField<T>::getUrl() const
{
    return this->url;
}

template<class T>
std::string SmartField<T>::getBody() const
{
    return this->body;
}
