#include <iostream>
#include "mainwindow.h"
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QApplication>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <thread>
#include <mutex>
#include <QSerialPortInfo>
#include <QList>
#include <QPalette>
#include <QColor>
#include <QLineEdit>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1920, 1080);
    w.show();
    return a.exec();
}



