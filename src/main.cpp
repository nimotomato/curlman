#include "mainwindow.h"
#include "appsettings.h"
#include "persistence.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <curl/curl.h>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
        "QWidget { background-color: #0a0a0a; color: #33ff33; font-family: 'Courier New', Consolas, monospace; font-weight: bold; }"
        "QLineEdit, QTextEdit, QPlainTextEdit, QScrollArea, QWidget#scrollAreaWidgetContents { background-color: #000000; border: 1px solid #1f6b15; color: #33ff33; padding: 2px; }"
        "QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus { border: 1px solid #33ff33; }"
        "QPushButton { background-color: #111111; border: 1px solid #33ff33; color: #33ff33; padding: 4px; }"
        "QPushButton:hover { background-color: #33ff33; color: #000000; }"
        "QPushButton:pressed { background-color: #1f6b15; color: #ffffff; }"
        "QRadioButton::indicator { border: 1px solid #33ff33; width: 10px; height: 10px; background: #000000; }"
        "QRadioButton::indicator:checked { background: #33ff33; }"
        "QMenuBar, QMenu { background-color: #0a0a0a; color: #33ff33; border-bottom: 1px solid #1f6b15; }"
        "QMenuBar::item:selected, QMenu::item:selected { background-color: #33ff33; color: #000000; }"
        );

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "test_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    sqlite3 *db = nullptr;

    QDir dir(QCoreApplication::applicationDirPath() + "/storage");
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    QString dbPath = QCoreApplication::applicationDirPath()
                     + "/storage/app.db";

    int rc = sqlite3_open(
        dbPath.toUtf8().constData(),
        &db
        );
    QFileInfo info(dbPath);
    if (rc)
    {
        fprintf(stderr, "Failed to open database :%s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_exec(db,
                 "PRAGMA foreign_keys = ON;",
                 nullptr,
                 nullptr,
                 nullptr);

    Persistence p(db);
    p.runMigrations();

    AppSettings settings;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    MainWindow w(settings, p);
    w.show();

    int result = QApplication::exec();

    sqlite3_close(db);
    curl_global_cleanup();

    return result;
}
