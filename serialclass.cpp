#include "serialclass.h"

#include <QErrorMessage>
#include <QStringList>

SerialClass::SerialClass()
{
    StructSize = sizeof(recvpacket);
    printf("Size: %i\n", StructSize);
}


void SerialClass::Init(QString Port, int BaudRate){

    serial.setPortName(Port);

    switch (BaudRate) {
    case 115200:
        serial.setBaudRate(QSerialPort::Baud115200);
        break;
    case 9600:
        serial.setBaudRate(QSerialPort::Baud9600);
        break;

    default:
        break;
    }


    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::HardwareControl);
    if(serial.open(QIODevice::ReadWrite)){
        printf("Serial OK!\n");
    }else{
        QErrorMessage *error = new QErrorMessage();
        error->showMessage(serial.errorString());
        //error->message(serial.errorString());
    }

    connect(&serial, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void SerialClass::Close(){
    serial.close();
}

void SerialClass::ReadData(){
    m_readData.append(serial.readAll());
    serial.flush();
    //ui->plainTextEdit->appendPlainText(m_readData);


        for( int i=0;i<(m_readData.length()-1);i++)
        {

            if(*(m_readData.data())=='M'){
              if(*(m_readData.data()+1)=='E'){

                break;
              }
            }
            m_readData=m_readData.right(1);
        }


        if((*m_readData.data()=='M')&&(m_readData.length()>=StructSize)){

            memcpy(&recvpacket.record,m_readData.data(),StructSize);

            /*ui->label->setText(QString::number(receiv_data.variable.day));
            ui->label_2->setText(QString::number(receiv_data.variable.pressureBMP));
            ui->plainTextEdit->appendPlainText(QString(m_readData));*/
            m_readData.clear();
        }


        emit PacketUpdated();
}


QStringList SerialClass::ListDevices(){
    QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();

    serialPortInfoList.count();

    QStringList QSL;
    foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList) {
          QSL.append(serialPortInfo.portName());

    }

    return QSL;
}



