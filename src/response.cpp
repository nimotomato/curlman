#include "response.h"

#include <string>

const std::string Response::getBody() const
{
    return body;
}

void Response::setBody(std::string newBody)
{
    body = newBody;
}

const std::string Response::getResponseHeadersString() const
{
    return responseHeadersString;
}

void Response::setResponseHeadersString(std::string newHeaders)
{
    responseHeadersString = newHeaders;
}

const long Response::getStatusCode() const
{
    return statusCode;
}

void Response::setStatusCode(long newStatusCode)
{
    statusCode = newStatusCode;
}