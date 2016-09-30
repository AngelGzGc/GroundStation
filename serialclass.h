#ifndef SERIALCLASS_H
#define SERIALCLASS_H

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>
#include <QCoreApplication>
#include <QObject>
#include <QStringList>

union  data_union{
struct __attribute__ ((packed)) Received_t {
        uint32_t magicValueBegin;

        uint8_t  cutting;
                    uint16_t frecuencyTelecom;
                    uint8_t  stateASD;
                    uint32_t timeASD;
                    float    pressureASD;
                    uint32_t timeTemp;
                    uint8_t  stateTempOutside;
                    float    tempOutside;
                    uint8_t  stateTempBatteries;
                    float    tempBatteries;
                    uint8_t  stateTempMicro;
                    float    tempMicro;
                    uint8_t  stateAccel;
                    uint32_t timeAccel;
                    float    accelX;
                    float    accelY;
                    float    accelZ;
                    uint8_t  stateGyro;
                    uint32_t timeGyro;
                    float   gyroX;
                    float   gyroY;
                    float   gyroZ;
                    uint8_t stateMag;
                    uint32_t timeMag;
                    float   magX;
                    float   magY;
                    float   magZ;
                    uint8_t stateBMP;
                    uint32_t timeBMP;
                    float   pressureBMP;
                    float   tempBMP;
                    uint8_t stateGPS;
                    uint8_t stateLocus;
                    uint8_t stateNMEA;
                    uint32_t timeGPS;
                    int16_t hour;
                    int16_t minute;
                    int16_t seconds;
                    int16_t milliseconds;
                    int16_t day;
                    int16_t month;
                    int16_t year;
                    int16_t fix;
                    int16_t fixquality;
                    int16_t satellites;
                    float   latitude;
                    float   longitude;
                    float   hspeed;
                    float   angle;
                    float   altitude;
                    uint8_t stateSd;
                    uint8_t stateFile;
                    uint32_t timeXbee;
                    float    xbeeTemp;
                    uint8_t  signalSt;
                    uint8_t  dutyCycle;
                    uint32_t msgSent;
                    uint32_t msgLost;
                    uint32_t msgRecv;
                    uint32_t magicValueEnd;
    } 	variable;

    uint8_t record[sizeof(Received_t)];
};



class SerialClass: public QObject
{

Q_OBJECT

public:
    SerialClass();
    void Init(QString Port, int BaudRate);
    void Close();

    QStringList ListDevices();
    union data_union recvpacket;
    int StructSize;
private:
    QSerialPort serial;
    QByteArray  m_readData;





public slots:
    void ReadData();
signals:

    void PacketUpdated();

};

#endif // SERIALCLASS_H
