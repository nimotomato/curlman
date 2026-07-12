#pragma once
#define REQUEST_H

#include <string>
#include <curl/curl.h>

#include "appsettings.h"
#include "headervector.h"
#include "response.h"

struct AdvancedSettings {
    int timeoutSeconds;
};

class Request
{
public:
    Request(const AppSettings& settings);
    ~Request();

    enum class Method {
        GET,
        POST,
        PUT,
        PATCH,
        DELETE,
        CONNECT,
    };

    std::string getUrl() const;
    void setUrl(const std::string& new_url);

    HeaderVector& getHeaderVector();

    std::string getBody() const;
    void setBody(const std::string& new_body);

    Method getMethod() const;
    std::string getMethodString() const;
    void setMethod(const Method& new_method);

    // Saves the request to database
    int save() const;

    std::string toString() const;

    Response send();

private:
    std::string url;
    std::string body;
    Method method;
    CURL* httpHandle;
    AppSettings settings;
    HeaderVector headers;
    static size_t streamResponse(char *data, size_t size, size_t nmemb, void *userp);
};


