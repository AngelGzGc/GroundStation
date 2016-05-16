#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>
#include "serialclass.h"

#define N_bytes 174


namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Received_t receiv_data;

    int counter=0;


public slots:

    void on_close_B_clicked();

    void on_connect_B_clicked();

    void on_pushButton_clicked();

    void UpdateLabels();

private:

    Ui::MainWindow *ui;
    SerialClass *sc;
};

#endif // MAINWINDOW_H
