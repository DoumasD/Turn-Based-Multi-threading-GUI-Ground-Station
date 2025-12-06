#ifndef WORKERDISPLAY_H
#define WORKERDISPLAY_H
#include "sharedresource.h"
#include <atomic>
#include <QGridLayout>
#include <QLabel>
#include <QChartView>
#include <vector>

class workerdisplay : public QObject
{
    Q_OBJECT
public:
    explicit workerdisplay(int id, sharedResource* shres );
    ~workerdisplay();
    workerdisplay();
    sharedResource *shres;
    std::atomic_bool shouldstop;
    int id;
    QByteArray buffer;

public slots:
    void display();
    void stop();
    void parseTelemetry(string temp);

signals:
    void updateDisplay(vector<string> data);



};

#endif // WORKERDISPLAY_H
