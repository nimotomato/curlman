#pragma once // ifdef is c-style header guard. This is the c++ way

class AppSettings
{
public:
    AppSettings() = default; // no need to define in source file when you do not want to set any non default member variables


    const int getDefaultHeadersSize() const;
    const int getIsWebsocket() const;

private:
    int defaultHeadersSize = 20;
    bool isWebsocket = false;
};

#endif // APPSETTINGS_H
