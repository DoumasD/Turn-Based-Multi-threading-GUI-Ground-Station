#ifndef WORKERSAVE_H
#define WORKERSAVE_H
#include <QObject>
#include <QDebug>
#include <atomic>
#include "sharedresource.h"

class workersave: public QObject
{
    Q_OBJECT
public:
    workersave();
    workersave(int id, sharedResource *shres);
    ~workersave();
    sharedResource *shres;
    std::atomic_bool shouldstop;
    int id;

public slots:
    void saveToCSV();
    void stop();
};

#endif // WORKERSAVE_H
