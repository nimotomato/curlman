#include "appsettings.h"

AppSettings::AppSettings() : defaultHeadersSize(20), isWebsocket(false){
}




const int AppSettings::getDefaultHeadersSize() const
{
    return defaultHeadersSize;
}

const int AppSettings::getIsWebsocket() const
{
    return isWebsocket;
}