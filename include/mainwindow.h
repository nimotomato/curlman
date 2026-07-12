#pragma once
#define MAINWINDOW_H

#include <curl/curl.h>
#include "appsettings.h"
#include "request.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AppSettings& settings, QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_sendButton_clicked();

    void on_urlInput_editingFinished();

    void on_getRadioButton_clicked();

    void on_putRadioButton_clicked();

    void on_postRadioButton_clicked();

    void on_patchRadioButton_clicked();

    void on_deleteRadioButton_clicked();

    void on_headerInput1_editingFinished();

    void on_headerValueInput1_editingFinished();

    void on_connectionRadioButton_clicked();

    void on_headerInput2_editingFinished();

    void on_headerValueInput2_editingFinished();

    void on_headerInput3_editingFinished();

    void on_headerValueInput3_editingFinished();

    void on_bodyTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
    CURL* httpHandle = curl_easy_init();
    AppSettings settings;
    Request request;
};

