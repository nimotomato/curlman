#pragma once
#define RESPONSE_H

#include <string>

class Response
{
public:
    Response();

    const std::string getBody() const;
    void setBody(std::string newBody);

    const std::string getResponseHeadersString() const;
    void setResponseHeadersString(std::string newHeaders);

    const long getStatusCode() const;
    void setStatusCode(long newStatusCode);

private:
    std::string body;
    std::string responseHeadersString;
    long statusCode;
};

