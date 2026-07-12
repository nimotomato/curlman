#include "headervector.h"
#include "header.h"

#include <string.h>
#include <vector>

HeaderVector::HeaderVector(size_t initial_size)
    : headers(initial_size)
{}

const std::vector<Header>& HeaderVector::getHeaders() const
{
    return headers;
}

const curl_slist* HeaderVector::getHeadersSList()
{
    curl_slist* slist = NULL;

    for (const auto& header : getHeaders())
    {
        if (header.getKey() == "")
        {
            continue;
        }
        std::string formattedHeader = header.getKey() + ": " + header.getValue();

        slist = curl_slist_append(slist, formattedHeader.c_str());
    }


    return slist;
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

