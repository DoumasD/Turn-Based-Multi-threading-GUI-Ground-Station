#include "workerreader.h"
#include <QString>
#include <QSerialPort>
#include <QThread>
#include <QMutex>
#include "sharedresource.h"
using namespace std;


workerreader::workerreader(int id,QString port,QString rate, sharedResource* shres ): id(id),port(port),baudrate(rate),shres(shres) {
serialPort = new QSerialPort(this);
}

workerreader::~workerreader() {
        serialPort->close();
        qDebug() << "Worker Reader Destroyed";
}

void workerreader::openSerialConnection()
{
    serialPort->setPortName(port);

    switch(stoi(baudrate.toStdString())){
        case 9600:
        serialPort->setBaudRate(QSerialPort::Baud9600);
        break;
        case 19200:
        serialPort->setBaudRate(QSerialPort::Baud19200);
        break;
        case 38400:
        serialPort->setBaudRate(QSerialPort::Baud38400);
        break;
        case 57600:
        serialPort->setBaudRate(QSerialPort::Baud57600);
        break;
        case 115200:
        serialPort->setBaudRate(QSerialPort::Baud115200);
        break;
    }

    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setReadBufferSize(4096);

    if (serialPort->open(QIODevice::ReadWrite)) {
       qDebug() << "Open port success";
    } else {
       qDebug() <<"Failed to open serial port:";
    }
    connect(serialPort, &QSerialPort::readyRead, this, &workerreader::readSerialData);
}


void workerreader::readSerialData()
{
    QThread::msleep(1000);
    newData = serialPort->readLine();

    shres->lock.lock();
    while (shres->currentTurn != id) {
        shres->waitCondition.wait(&shres->lock);
        QThread::msleep(100);
    }

    qDebug() <<"Received data:" << newData.toStdString();
    shres->data =newData;
    shres->currentTurn = (id +1);
    shres->lock.unlock();
    shres->waitCondition.wakeAll();
}

void workerreader::open_PFill_method(){
    serialPort->write("1");
}

void workerreader::close_PFill_method(){
    serialPort->write("2");
}

void workerreader::open_POIV_method(){
    serialPort->write("3");
}

void workerreader::close_POIV_method(){
    serialPort->write("4");
}

void workerreader::open_OXIFill_method(){
    serialPort->write("5");
}

void workerreader::close_OXIFill_method(){
    serialPort->write("6");
}

void workerreader::launch_method(){
    serialPort->write("7");
}

void workerreader::abort_method(){
    serialPort->write("8");
}
