#include "headervector.h"
#include "header.h"

#include <string.h>
#include <vector>

HeaderVector::HeaderVector(size_t initial_size)
    : headers(initial_size)
    , slistHeaders(nullptr)
{}

const std::vector<Header>& HeaderVector::getHeaders() const
{
    return headers;
}

const curl_slist* HeaderVector::getHeadersSList()
{
    if (slistHeaders != nullptr) {
        curl_slist_free_all(slistHeaders);
        slistHeaders = nullptr;
    }

    for (const auto& header : getHeaders())
    {
        if (header.getKey() == "")
        {
            continue;
        }
        std::string formattedHeader = header.getKey() + ": " + header.getValue();

        slistHeaders = curl_slist_append(slistHeaders, formattedHeader.c_str());
    }


    // Can you assume that this HeaderVector object will outlive the use of slistHeaders? Who owns this memory I find not obvious. Risk for use after free or double free
    return slistHeaders;
}

void HeaderVector::insertHeader(size_t index, const Header& newHeader)
{
    if (index >= headers.size()){
        headers.resize(index + 1);
    }

    headers[index] = newHeader;
}

void HeaderVector::setHeaderKey(size_t index, const std::string &newKey){
    if (index >= headers.size())
    {
        Header h(newKey, "");
        insertHeader(index, h);
    } else {
        Header &h = headers[index];
        h.setKey(newKey);
    }
}

void HeaderVector::setHeaderValue(size_t index, const std::string &newValue){
    if (index >= headers.size())
    {
        Header h("", newValue);
        insertHeader(index, h);
    } else {
        Header &h = headers[index];
        h.setValue(newValue);
    }
}
