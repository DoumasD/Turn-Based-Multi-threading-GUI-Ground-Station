#include "workersave.h"
#include <QThread>
#include <QFile>
workersave::workersave() {}

workersave::workersave(int id,sharedResource* shres): id(id),shres(shres),shouldstop(false) {}

workersave::~workersave(){
    qDebug() << "Worker save is Destroyed";
    stop();
}

void workersave::saveToCSV(){
    QFile file("./test.csv");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Mission_time,Temp1,Temp2,Pressure1,Pressure2,Temp3,Temp4,Pressure3,Pressure4,Temp5,Temp6,Pressure5,Pressure6,Pressurant_Fill_Indicator,Pressurant_Oxidizer_Indicator,Oxidizer_Fill_Indicator,Oxidizer_Combustion_Indicator\n";
        while(!shouldstop.load())
        {
            shres->lock.lock();
            while (shres->currentTurn != id) {
                shres->waitCondition.wait(&shres->lock);
                QThread::msleep(100);
            }
            out << shres->data;
            qDebug()  <<"In save worker thread";
            shres->currentTurn = 0;
            shres->lock.unlock();
            shres->waitCondition.wakeAll();
        }
        file.close();
    }
}

void workersave::stop(){
    shouldstop=true;
}
