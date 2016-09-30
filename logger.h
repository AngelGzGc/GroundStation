#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>
#include <QQuickView>
#include <QQuickItem>
#include <QMainWindow>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = 0);
    ~Logger();

    void Init(QString fin);
    void Log(QByteArray bytes);

    void Close();

signals:

public slots:

private:
    QFile fp;
};

#endif // LOGGER_H
