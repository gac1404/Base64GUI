#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "base64.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//encoder module
void MainWindow::on_pushButtonOpenFolderEncoder_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");

    ui->lineEditEncoder->setText(filePath);
}

void MainWindow::on_pushButtonEncode_clicked()
{
    if(ui->lineEditEncoder->text() == "")
    {
        QMessageBox::about(this, "Error" , "Wrong file path");
    }
    else
    {
        Base64 b64;
        b64.encode(ui->lineEditEncoder->text().toStdString());
        QMessageBox::about(this, "Status" , "Done");
    }
}

//decoder module
void MainWindow::on_pushButtonOpenFolderDecoder_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");
    ui->lineEditDecoder->setText(filePath);
}

void MainWindow::on_pushButtonDecode_clicked()
{
     std::string temp = ui->lineEditDecoder->text().toStdString();
     temp = std::string(temp.end() - 3 , temp.end());
     if(temp == ".b64" || ui->textEditFileType->toPlainText() != "")
     {
         Base64 b64;
         b64.decode(ui->lineEditDecoder->text().toStdString() , ui->textEditFileType->toPlainText().toStdString());
         QMessageBox::about(this, "Status" , "Done");
     }
     else
     {
         QMessageBox::about(this, "Error" , "Wrong file path");
     }
}


