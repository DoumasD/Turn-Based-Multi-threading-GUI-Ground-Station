#include "workerdisplay.h"
#include <QThread>
#include <QWaitCondition>
#include <atomic>
#include <QByteArray>
#include <QLabel>
#include <sstream>
#include <string>
#include <QString>
using namespace std;


workerdisplay::workerdisplay() {}

workerdisplay::workerdisplay(int id,sharedResource* shres ): id(id), shres(shres), shouldstop(false) {}

workerdisplay::~workerdisplay() {
    qDebug() << "Worker Display Destroyed";
    stop();
}

void workerdisplay::display()
{
    while(!shouldstop.load())
    {
        shres->lock.lock();
        while (shres->currentTurn != id) {
            shres->waitCondition.wait(&shres->lock);
            QThread::msleep(100);
        }

        qDebug() << "In display thread"<< shres->data;
        buffer= shres->data;

        if(buffer.size() >= 81)
        {
            parseTelemetry(buffer.toStdString());
        }

        shres->currentTurn = (id +1);
        shres->lock.unlock();
        shres->waitCondition.wakeAll();
    }
}

void workerdisplay::stop()
{
    shouldstop=true;  /// probabily needs to move the desctructor
}

/*
1.) Parse buffer string
2.) emit data to the parent thread
*/
void workerdisplay::parseTelemetry(string temp)
{
    vector<string> data;
    stringstream ss(temp);
    string value;

    while(std::getline(ss,value,','))
    {
        data.push_back(value);
    }
    emit updateDisplay(data);
}
