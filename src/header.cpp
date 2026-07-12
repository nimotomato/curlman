#include "header.h"

Header::Header() : key(""), value("")
{
}

Header::Header(const std::string &newKey, const std::string &newValue) : key(newKey), value(newValue){}

std::string Header::getKey() const
{
    return key;
}

void Header::setKey(const std::string &newKey) {
    key = newKey;
}

std::string Header::getValue() const
{
    return value;
}

void Header::setValue(const std::string &newValue) {
    value = newValue;
}