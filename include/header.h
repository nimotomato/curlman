#pragma once

#define HEADER_H
#include <string>

class Header
{
public:
    Header();
    Header(const std::string &new_key, const std::string &new_value);

    std::string getKey() const;
    void setKey(const std::string &new_key);

    std::string getValue() const;
    void setValue(const std::string &new_value);



private:
    std::string key;
    std::string value;
};

