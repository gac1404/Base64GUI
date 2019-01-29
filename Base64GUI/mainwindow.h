#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonOpenFolder_clicked();

    void on_pushButtonEncode_clicked();

    void on_pushButtonOpenFolderDecode_clicked();

    void on_pushButtonOpenFolderEncoder_clicked();

    void on_pushButtonDecode_clicked();

    void on_pushButtonOpenFolder_2_clicked();

    void on_pushButtonOpenFolderDecoder_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
