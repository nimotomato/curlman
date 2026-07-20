#pragma once

class AppSettings
{
public:
    AppSettings() = default;


    const int getDefaultHeadersSize() const;
    const int getIsWebsocket() const;

private:
    int defaultHeadersSize = 20;
    bool isWebsocket = false;
};

