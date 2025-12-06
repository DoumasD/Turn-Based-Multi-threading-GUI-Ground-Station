#ifndef WORKERREADER_H
#define WORKERREADER_H
#include <QObject>
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QMutex>
#include "sharedresource.h"

using namespace std;

class workerreader : public QObject
{
    Q_OBJECT
public:
    explicit workerreader(int id, QString port,QString rate, sharedResource* shres);
    ~workerreader();

public slots:
    void openSerialConnection();
    void readSerialData();
    void open_PFill_method();
    void close_PFill_method();
    void open_POIV_method();
    void close_POIV_method();
    void open_OXIFill_method();
    void close_OXIFill_method();
    void launch_method();
    void abort_method();

private:
    QString port;
    QString baudrate;
    QSerialPort *serialPort;
    QByteArray newData;
    QMutex buffLock;
    sharedResource *shres;
    int id;

};

#endif // WORKERREADER_H
