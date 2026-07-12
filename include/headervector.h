#pragma once

#include "header.h"
#include <vector>
#include <curl/curl.h>

class HeaderVector
{
public:
    HeaderVector(size_t initial_size);

    const std::vector<Header>& getHeaders() const;
    const curl_slist* getHeadersSList();
    void insertHeader(size_t index, const Header& newHeader);
    void setHeaderKey(size_t index, const std::string& newKey);
    void setHeaderValue(size_t index, const std::string& newValue);

private:
    std::vector<Header> headers;
};
