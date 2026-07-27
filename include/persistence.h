#pragma once

#define PERSISTENCE_H
#include <sqlite3.h>
#include <qstring.h>

class Persistence
{
public:
    struct Request
    {
        int64_t id = 0;
        QString method;
        QString body;
    };
    struct RequestHeader
    {
        int64_t requestId;
        QString key;
        QString value;
    };
    struct Response
    {
        int64_t requestId;
        int statusCode;
        QString body;
        int responseTime;
    };


    Persistence(sqlite3 *db);

    void runMigrations();
    void insertRequest(const Request& r);
    void insertRequestHeaders(const std::vector<RequestHeader>& headers);
    void insertResponse(const Response& r);

private:
    std::string readFile(const QString& path);

    sqlite3 *db;
};
