#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialclass.h"

#include <QtSerialPort/QtSerialPort>
#include <QTextStream>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPortInfo>
#include <QCoreApplication>
#include <QPlainTextEdit>
#include <QVariant>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QMetaObject>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuración puerto serie.
    sc = new SerialClass();
    ui->serial_combo->addItems(sc->ListDevices());

    QObject::connect(sc, SIGNAL(PacketUpdated()), this, SLOT(UpdateLabels()));


    // Mapa QML

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(400, 400);
    //container->setMaximumSize(500, 200);
    container->setFocusPolicy(Qt::TabFocus);
    view->rootContext()->setContextProperty("latitud",12.917352466802262);

    view->setSource(QUrl::fromLocalFile("/home/Angel/LEEM/Angel/GUI_rockoon/main.qml"));

    ui->verticalLayout->addWidget(container);
    object = view->rootObject();

    // Logger
    Log = new Logger();
    Log->Init("Log.txt");

}

MainWindow::~MainWindow()
{
    delete ui;
    //serial.close();
    Log->Close();
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

    //ui->plainTextEdit->appendPlainText(QString(sc->recvpacket.variable.magicValueBegin));
    //ui->label->setText(QString::number(sc->recvpacket.variable.seconds));


    double latitud = sc->recvpacket.variable.latitude;
    double longitud = sc->recvpacket.variable.longitude;

    ui->label->setText(QString::number(latitud));
    ui->label_2->setText(QString::number(longitud));

    // Y sucede la magia....
    QVariant returnedValue;

    QMetaObject::invokeMethod(object, "updateCenter",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, latitud),Q_ARG(QVariant, longitud));

    QMetaObject::invokeMethod(object, "moveCircle",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, latitud),Q_ARG(QVariant, longitud));



    QMetaObject::invokeMethod(object, "addCoord",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, latitud),Q_ARG(QVariant, longitud));

    //Después de la magia...

    Log->Log(QByteArray::fromRawData((const char*)sc->recvpacket.record, sc->StructSize));
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
