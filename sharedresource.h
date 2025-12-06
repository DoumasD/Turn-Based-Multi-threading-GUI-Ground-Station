#ifndef SHAREDRESOURCE_H
#define SHAREDRESOURCE_H

#include <QWidget>
#include <QMutex>
#include <QWaitCondition>
#include <QSerialPort>

using namespace std;
class sharedResource: public QObject
{
    Q_OBJECT
public:
    QMutex lock;
    QWaitCondition waitCondition;
    QByteArray data;
    int currentTurn = 0;


};
#endif // SHAREDRESOURCE_H
