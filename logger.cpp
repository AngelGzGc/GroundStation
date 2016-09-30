#include "logger.h"
#include <QFile>


Logger::Logger(QObject *parent) : QObject(parent)
{

}

void Logger::Init(QString fin){
    fp.setFileName(fin);
    fp.open(QIODevice::WriteOnly|QIODevice::Truncate| QIODevice::Text);
}

void Logger::Log(QByteArray bytes){
    fp.write(bytes, bytes.length());
    fp.write("\n");
}

void Logger::Close(){
    fp.close();
}

Logger::~Logger(){
    fp.close();
}
