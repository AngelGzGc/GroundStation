#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialclass.h"

#include <QtSerialPort/QtSerialPort>
#include <QTextStream>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPortInfo>
#include <QCoreApplication>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sc = new SerialClass();
    ui->serial_combo->addItems(sc->ListDevices());

    QObject::connect(sc, SIGNAL(PacketUpdated()), this, SLOT(UpdateLabels()));

}

MainWindow::~MainWindow()
{
    delete ui;
    //serial.close();
}


void MainWindow::on_close_B_clicked()
{
   ui->connect_B->setEnabled(true);
   ui->serial_combo->setEnabled(true);
   ui->baudrate_combo->setEnabled(true);
   sc->Close();
   //serial.close();
   //connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

void MainWindow::on_connect_B_clicked()
{

    //open_serial();
    sc->Init(
             ui->serial_combo->currentText(),
             ui->baudrate_combo->currentText().toInt()
    );

    //serial.flush();
    ui->connect_B->setEnabled(false);
    ui->close_B->setEnabled(true);
    ui->serial_combo->setEnabled(false);
    ui->baudrate_combo->setEnabled(false);


}

void MainWindow::UpdateLabels(){

    ui->plainTextEdit->appendPlainText(QString(sc->recvpacket.variable.magicValueBegin));
    ui->label->setText(QString::number(sc->recvpacket.variable.seconds));
}


void MainWindow::on_pushButton_clicked()
{
    QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();

       serialPortInfoList.count();
       ui->serial_combo->clear();


      foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList) {
              ui->serial_combo->addItem(serialPortInfo.portName());

      }
}
