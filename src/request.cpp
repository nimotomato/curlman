#include "request.h"
#include "headervector.h"
#include "response.h"

#include <iostream>
#include <curl/curl.h>
#include <format>
#include <QDebug>


Request::Request(const AppSettings& settings)
    : settings(settings)
    , headers(settings.getDefaultHeadersSize())
{
    httpHandle = curl_easy_init();
    if (!httpHandle)
    {
        qDebug() << "Failed to init http handle.";
    }
}

Request::~Request()
{
    curl_easy_cleanup(httpHandle);
}

std::string Request::getUrl() const
{
    return url;
}

void Request::setUrl(const std::string &newUrl)
{
    url = newUrl;
}

HeaderVector& Request::getHeaderVector()
{
    return headers;
}

std::string Request::getBody() const
{
    return body;
}

void Request::setBody(const std::string &newBody)
{
    body = newBody;
}

Request::Method Request::getMethod() const
{
    return method;
}

std::string Request::getMethodString() const
{
    switch (Request::method)
    {
    case Method::POST:
        return "POST";
    case Method::PATCH:
        return "PATCH";
    case Method::PUT:
        return "PUT";
    case Method::DELETE:
        return "DELETE";
    case Method::CONNECT:
        return "CONNECT";
    default:
        return "";
    }
}

void Request::setMethod(const Method &newMethod)
{
    method = newMethod;
}
int Request::save() const
{
    return 0;
}

std::string Request::toString() const
{
    std::string curlString = "curl -v -i ";
    std::string methodString = getMethodString();
    if (methodString != "") {
        methodString = std::format("-X {} \\n", methodString);
    }

    std::string headersString = "";
    for (const auto& header : headers.getHeaders()){
        if (header.getKey() == "")
        {
            continue;
        }
        headersString += std::format("-H \"{}: {}\" \\n", header.getKey(), header.getValue());
    }

    std::string bodyString = getBody();
    if (bodyString != ""){
        bodyString = std::format("-d '{}' \\n", bodyString);
    }

    return std::format("{}{}{}{}{}\n", curlString, methodString, headersString, bodyString, getUrl());
}

Response Request::send()
{
    // handle url
    std::string url = getUrl();
    curl_easy_setopt(httpHandle, CURLOPT_URL, url.c_str());

    // handle headers
    curl_slist* h = NULL;
    for (const auto& header : headers.getHeaders()){
        if (header.getKey() == "")
        {
            continue;
        }

        std::string formattedHeader = header.getKey() + ": " + header.getValue();
        h = curl_slist_append(h, formattedHeader.c_str());
    }
    curl_easy_setopt(httpHandle, CURLOPT_HTTPHEADER, h);

    // handle method
    switch (method)
    {
    case Request::Method::GET:
        break;
    case Request::Method::POST:
        curl_easy_setopt(httpHandle, CURLOPT_CUSTOMREQUEST, "POST");
        break;
    case Request::Method::PATCH:
        curl_easy_setopt(httpHandle, CURLOPT_CUSTOMREQUEST, "PATCH");
        break;
    case Request::Method::PUT:
        curl_easy_setopt(httpHandle, CURLOPT_CUSTOMREQUEST, "PUT");
        break;
    case Request::Method::DELETE:
        curl_easy_setopt(httpHandle, CURLOPT_CUSTOMREQUEST, "DELETE");
        break;
    case Request::Method::CONNECT:
        curl_easy_setopt(httpHandle, CURLOPT_CUSTOMREQUEST, "CONNECT");
        long connType = 1L;

        if (settings.getIsWebsocket())
        {
            connType = 2L;
        }

        curl_easy_setopt(httpHandle, CURLOPT_CONNECT_ONLY, &connType);
        break;
    }

    // handle body
    std::string body = getBody();
    if (body != "" && method != Method::GET && method != Method::CONNECT){
        curl_easy_setopt(httpHandle, CURLOPT_POSTFIELDSIZE, body.size());
        curl_easy_setopt(httpHandle, CURLOPT_POSTFIELDS, body.c_str());
    }

    // handle response
    curl_easy_setopt(httpHandle, CURLOPT_WRITEFUNCTION, Request::streamResponse);
    std::ostringstream responseBody;
    curl_easy_setopt(httpHandle, CURLOPT_WRITEDATA, &responseBody);

    // handle response headers
    std::ostringstream responseHeaders;
    curl_easy_setopt(httpHandle, CURLOPT_HEADERFUNCTION, Request::streamResponse);
    curl_easy_setopt(httpHandle, CURLOPT_HEADERDATA, &responseHeaders);

    // handle execution
    CURLcode result = curl_easy_perform(httpHandle);
    if (result != CURLE_OK)
        {
            curl_slist_free_all(h);
            qDebug() << "curl_easy_perform() failed: " << curl_easy_strerror(result);
            throw std::runtime_error(curl_easy_strerror(result));
        }


    // handle status code
    long statusCode = 0;
    curl_easy_getinfo(httpHandle, CURLINFO_RESPONSE_CODE, &statusCode);

    qDebug() << "Status Code:" << statusCode;
    qDebug() << "Headers:" << QString::fromStdString(responseHeaders.str());
    qDebug() << "Body:" << QString::fromStdString(responseBody.str());

    Response r;
    r.setBody(responseBody.str());
    r.setResponseHeadersString(responseHeaders.str());
    r.setStatusCode(statusCode);
    curl_slist_free_all(h);

    return r;
}

size_t Request::streamResponse(char *data, size_t size, size_t nmemb, void *userp)
{
    // Cast the user pointer to an ostream and write the data to it
    *static_cast<std::ostream*>(userp) << data;

    // Return the number of bytes processed
    return size * nmemb;
}
