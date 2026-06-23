#ifndef HEADERVECTOR_H
#define HEADERVECTOR_H

#include "header.h"
#include <memory>
#include <vector>
#include <curl/curl.h>

class HeaderVector
{
public:
    HeaderVector(size_t initial_size);
    // ~HeaderVector(); // when you define an explicit destructor, the compiler can no longer auto generate some other useful methods. See https://en.cppreference.com/cpp/language/rule_of_three
                     // To avoid this try below fix for member sListHeaders
    const std::vector<Header>& getHeaders() const;
    const curl_slist* getHeadersSList();
    void insertHeader(size_t index, const Header& newHeader);
    void setHeaderKey(size_t index, const std::string& newKey);
    void setHeaderValue(size_t index, const std::string& newValue);

private:
    std::vector<Header> headers;
    std::shared_ptr<curl_slist> slistHeaders = std::shared_ptr<curl_slist>{nullptr, curl_slist_free_all}; // set the destructor function, might be wrong syntax

};


#endif //
