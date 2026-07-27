#include "persistence.h"
#include "QCoreApplication"
#include "QDir"
#include <fstream>
#include <sstream>
#include <sqlite3.h>

Persistence::Persistence(sqlite3 *db) : db(db){}

std::string Persistence::readFile(const QString& path)
{
    std::ifstream file(path.toStdString());

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void Persistence::runMigrations()
{
    QString migrationPath = QCoreApplication::applicationDirPath() + "/migrations";

    QDir migrations(migrationPath);

    QStringList files = migrations.entryList(
        QStringList() << "*.sql",
        QDir::Files,
        QDir::Name
    );

    sqlite3_exec(db, "BEGIN;", nullptr, nullptr, nullptr);

    for (const QString& file : files){
        QString fullPath = migrations.absoluteFilePath(file);
        QString id = QFileInfo(file).baseName();
        std::string sql = readFile(fullPath);

        char* err = nullptr;
        int rc = sqlite3_exec(
            db,
            sql.c_str(),
            nullptr,
            nullptr,
            &err
        );
        if (rc != SQLITE_OK)
        {
            fprintf(stderr,
                    "Migration failed: %s\n",
                    err);

            sqlite3_free(err);
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }
    }

    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
    return ;
}

