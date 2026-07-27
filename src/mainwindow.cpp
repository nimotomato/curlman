#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appsettings.h"
#include "request.h"

#include <curl/curl.h>
#include <QErrorMessage>

MainWindow::MainWindow(AppSettings& settings, Persistence& p, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings(settings)
    , request(settings, p){
    ui->setupUi(this);
    setWindowTitle("curlman");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QErrorMessage* msg = new QErrorMessage(this);
    try {
        Response r = request.send();
        ui->resultText->setText(QString::fromStdString(r.getBody()));
        ui->statusCode->setText(QString::fromStdString(std::to_string(r.getStatusCode())));
    } catch (const std::exception& e) {
        msg->showMessage(e.what());
    }
}

void MainWindow::on_urlInput_editingFinished()
{
    request.setUrl(ui->urlInput->text().trimmed().toStdString());
}

void MainWindow::on_getRadioButton_clicked()
{
    request.setMethod(Request::Method::GET);
}

void MainWindow::on_putRadioButton_clicked()
{
    request.setMethod(Request::Method::PATCH);
}

void MainWindow::on_postRadioButton_clicked()
{
    request.setMethod(Request::Method::POST);
}

void MainWindow::on_patchRadioButton_clicked()
{
    request.setMethod(Request::Method::PATCH);
}

void MainWindow::on_deleteRadioButton_clicked()
{
    request.setMethod(Request::Method::DELETE);
}
void MainWindow::on_connectionRadioButton_clicked()
{
    request.setMethod(Request::Method::CONNECT);
}
void MainWindow::on_headerInput1_editingFinished()
{
   const int inputIndex = 0;
   const std::string newKey = ui->headerInput1->text().trimmed().toStdString();

   request.getHeaderVector().setHeaderKey(inputIndex, newKey);
}

void MainWindow::on_headerValueInput1_editingFinished()
{
    const int inputIndex = 0;
    const std::string newValue = ui->headerValueInput1->text().trimmed().toStdString();

    request.getHeaderVector().setHeaderValue(inputIndex, newValue);
}

void MainWindow::on_headerInput2_editingFinished()
{
    const int inputIndex = 1;
    const std::string newKey = ui->headerInput2->text().trimmed().toStdString();

    request.getHeaderVector().setHeaderKey(inputIndex, newKey);
}


void MainWindow::on_headerValueInput2_editingFinished()
{
    const int inputIndex = 1;
    const std::string newValue = ui->headerValueInput2->text().trimmed().toStdString();

    request.getHeaderVector().setHeaderValue(inputIndex, newValue);
}


void MainWindow::on_headerInput3_editingFinished()
{
    const int inputIndex = 2;
    const std::string newKey = ui->headerInput3->text().trimmed().toStdString();

    request.getHeaderVector().setHeaderKey(inputIndex, newKey);
}


void MainWindow::on_headerValueInput3_editingFinished()
{
    const int inputIndex = 2;
    const std::string newValue = ui->headerValueInput3->text().trimmed().toStdString();

    request.getHeaderVector().setHeaderValue(inputIndex, newValue);
}


void MainWindow::on_bodyTextEdit_textChanged()
{
    request.setBody(ui->bodyTextEdit->toPlainText().trimmed().toStdString());
}


