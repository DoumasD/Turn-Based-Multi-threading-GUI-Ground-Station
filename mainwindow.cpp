#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>
//#include <iostream>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QString>
#include <QList>
#include <QThread>
#include <QObject>
#include "sharedresource.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");
    series1 = new QLineSeries(this);
    series2 = new QLineSeries(this);
    series3 = new QLineSeries(this);
    series4 = new QLineSeries(this);
    series5 = new QLineSeries(this);
    series6 = new QLineSeries(this);
    series1->setName("Pressure");
    series2->setName("Temperature");
    series3->setName("Pressure");
    series4->setName("Temperature");
    series5->setName("Pressure");
    series6->setName("Temperature");
    chart1 = new QChart();
    chart1->legend(); // Hide the legend for a simple chart
    chart1->addSeries(series1);
    chart1->addSeries(series2);    // Add the series to the chart
    chart1->setTitle("Pressurant Pressure & Temperature"); // Set the chart title
    chart1->setTitleBrush(QBrush(Qt::white));
    chart1->setBackgroundBrush(QBrush(QColor("black")));
    axisX = new QValueAxis();
    axisX->setRange(0, 100); // Initial range
    axisX->setTitleText("Time (Seconds)");
    chart1->addAxis(axisX, Qt::AlignBottom);
    series1->attachAxis(axisX);
    axisY = new QValueAxis();
    axisY->setRange(-300, 300); // Initial range
    axisY->setTitleText("Pressure (Psi)");
    chart1->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisY);
    axisY2 = new QValueAxis();
    axisY2->setRange(-300, 300); // Initial range
    axisY2->setTitleText("Temperature (C)");
    chart1->addAxis(axisY2, Qt::AlignRight);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY2);
    chart2 = new QChart();
    chart2->legend(); // Hide the legend for a simple chart
    chart2->addSeries(series3); // Add the series to the chart
    chart2->addSeries(series4);
    chart2->setTitle("Oxidizer Pressure & Temperature"); // Set the chart title
    chart2->setTitleBrush(QBrush(Qt::white));
    chart2->setBackgroundBrush(QBrush(QColor("black")));
    axisX2 = new QValueAxis();
    axisX2->setRange(0, 100); // Initial range
    axisX2->setTitleText("Time (Seconds)");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    axY2 = new QValueAxis();
    axY2->setRange(-300, 300); // Initial range
    axY2->setTitleText("Pressure (Psi)");
    chart2->addAxis(axY2, Qt::AlignLeft);
    series3->attachAxis(axY2);
    aY2 = new QValueAxis();
    aY2->setRange(-300, 300); // Initial range
    aY2->setTitleText("Temperature (C)");
    chart2->addAxis(aY2, Qt::AlignRight);
    series4->attachAxis(axisX2);
    series4->attachAxis(aY2);
    chart3 = new QChart();
    chart3->legend(); // Hide the legend for a simple chart
    chart3->addSeries(series5); // Add the series to the chart
    chart3->addSeries(series6);
    chart3->setTitle("Combustion Pressure & Temperature"); // Set the chart title
    chart3->setTitleBrush(QBrush(Qt::white));
    chart3->setBackgroundBrush(QBrush(QColor("black")));//#404040
    axisX3 = new QValueAxis();
    axisX3->setRange(0, 100); // Initial range
    axisX3->setTitleText("Time (Seconds)");
    chart3->addAxis(axisX3, Qt::AlignBottom);
    alY2 = new QValueAxis();
    alY2->setRange(-300, 300); // Initial range
    alY2->setTitleText("Pressure (Psi)");
    chart3->addAxis(alY2, Qt::AlignLeft);
    series5->attachAxis(alY2);
    a2 = new QValueAxis();
    a2->setRange(-300, 300); // Initial range
    a2->setTitleText("Temperature (C)");
    chart3->addAxis(a2, Qt::AlignRight);
    series6->attachAxis(axisX3);
    series6->attachAxis(a2);
    chartView1 = new QChartView(chart1,this);
    chartView2 = new QChartView(chart2,this);
    chartView3 = new QChartView(chart3,this);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView3->setRenderHint(QPainter::Antialiasing);
    chartView1->setStyleSheet("QChartView { border: 2px solid #7DF9FF; }");
    chartView2->setStyleSheet("QChartView { border: 2px solid #7DF9FF; }");
    chartView3->setStyleSheet("QChartView { border: 2px solid #7DF9FF; }");
    chartView1->setBaseSize(40,80);
    s= new QSize(800,800);
    chartView1->setMaximumSize(*s);
    chartView2->setMaximumSize(*s);
    chartView3->setMaximumSize(*s);
    // Labels
    l1 = new QLabel("Tanks:");
    l2 = new QLabel("Pressurant:");
    l3 = new QLabel("Oxidizer:");
    l4 = new QLabel("Combusition:");
    l5 = new QLabel("Temperature (C):");
    l6 = new QLabel("N/A");
    l7 = new QLabel("N/A");
    l8 = new QLabel("N/A");
    l9 = new QLabel("Pressure  (psi):");
    l10 = new QLabel("N/A");
    l11 = new QLabel("N/A");
    l12 = new QLabel("N/A");
    // Values on/off indicators
    l13 = new QLabel("Values:");
    l14 = new QLabel("Pressurant_Fill:");
    l15 = new QLabel("Pressurant_Oxidizer:");
    l16 = new QLabel("Oxidizer_Fill:");
    l17 = new QLabel("Oxi_Combustion:");
    l18 = new QLabel("Open/Closed");
    l19 = new QLabel("N/A");
    l20 = new QLabel("N/A");
    l21 = new QLabel("N/A");
    l22 = new QLabel("N/A");
    l6->setAlignment(Qt::AlignCenter);
    l7->setAlignment(Qt::AlignCenter);
    l8->setAlignment(Qt::AlignCenter);
    l10->setAlignment(Qt::AlignCenter);
    l11->setAlignment(Qt::AlignCenter);
    l12->setAlignment(Qt::AlignCenter);
    l19->setAlignment(Qt::AlignCenter);
    l20->setAlignment(Qt::AlignCenter);
    l21->setAlignment(Qt::AlignCenter);
    l22->setAlignment(Qt::AlignCenter);
    l1->setStyleSheet("color: white;");
    l2->setStyleSheet("color: white;");
    l3->setStyleSheet("color: white;");
    l4->setStyleSheet("color: white;");
    l5->setStyleSheet("color: white;");
    l6->setStyleSheet("color: white;");
    l7->setStyleSheet("color: white;");
    l8->setStyleSheet("color: white;");
    l9->setStyleSheet("color: white;");
    l10->setStyleSheet("color: white;");
    l11->setStyleSheet("color: white;");
    l12->setStyleSheet("color: white;");
    l13->setStyleSheet("color: white;");
    l14->setStyleSheet("color: white;");
    l15->setStyleSheet("color: white;");
    l16->setStyleSheet("color: white;");
    l17->setStyleSheet("color: white;");
    l18->setStyleSheet("color: white;");
    l19->setStyleSheet("color: white;");
    l20->setStyleSheet("color: white;");
    l21->setStyleSheet("color: white;");
    l22->setStyleSheet("color: white;");

    open_PFill= new QPushButton("Open P-Fill");
    close_PFill= new QPushButton("Close P-Fill");
    open_POIV= new QPushButton("Open POIV");
    close_POIV= new QPushButton("Close POIV");
    open_OXIFill= new QPushButton("Open OXI-Fill");
    close_OXIFill= new QPushButton("Close OXI-Fill");
    launch= new QPushButton("Launch",this);
    abort= new QPushButton("Abort");
    open_PFill->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    close_PFill->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    open_POIV->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    close_POIV->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    open_OXIFill->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    close_OXIFill->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    launch->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    abort->setStyleSheet("color: white;border: 2px solid #7DF9FF;");

    f = new QFrame();
    f->setLineWidth(1);
    f->setFrameStyle(2);
    f->setStyleSheet("QFrame { border: 2px solid #7DF9FF;  }");
    gridLayout = new QGridLayout(ui->centralwidget);
    gridLayout->addWidget(chartView1, 0, 0);
    gridLayout->addWidget(chartView2, 0, 1);
    gridLayout->addWidget(chartView3, 0, 2);
    gridLayout->addWidget(f,1,0,3,3);

    QGridLayout *dataTableLayout = new QGridLayout();
    dataTableLayout->addWidget(l1, 0, 1);
    dataTableLayout->addWidget(l2, 0, 2);
    dataTableLayout->addWidget(l3, 0, 3);
    dataTableLayout->addWidget(l4, 0, 4);
    dataTableLayout->addWidget(l5, 1, 1);
    dataTableLayout->addWidget(l6, 1, 2);
    dataTableLayout->addWidget(l7, 1, 3);
    dataTableLayout->addWidget(l8, 1, 4);
    dataTableLayout->addWidget(l9, 2, 1);
    dataTableLayout->addWidget(l10, 2, 2);
    dataTableLayout->addWidget(l11, 2, 3);
    dataTableLayout->addWidget(l12, 2, 4);

    QGridLayout *valvesTableLayout = new QGridLayout();
    valvesTableLayout->addWidget(l13,0,5);
    valvesTableLayout->addWidget(l14,1,5);
    valvesTableLayout->addWidget(l15,2,5);
    valvesTableLayout->addWidget(l16,3,5);
    valvesTableLayout->addWidget(l17,4,5);
    valvesTableLayout->addWidget(l18,0,6);
    valvesTableLayout->addWidget(l19,1,6);
    valvesTableLayout->addWidget(l20,2,6);
    valvesTableLayout->addWidget(l21,3,6);
    valvesTableLayout->addWidget(l22,4,6);


    QGridLayout *commandButtonsTableLayout = new QGridLayout();
    commandButtonsTableLayout->addWidget(open_PFill,0,7);
    commandButtonsTableLayout->addWidget(close_PFill,1,7);
    commandButtonsTableLayout->addWidget(open_POIV,2,7);
    commandButtonsTableLayout->addWidget(close_POIV,3,7);
    commandButtonsTableLayout->addWidget(open_OXIFill,0,8);
    commandButtonsTableLayout->addWidget(close_OXIFill,1,8);
    commandButtonsTableLayout->addWidget(launch,2,8);
    commandButtonsTableLayout->addWidget(abort,3,8);

    controlPanelLayout = new QHBoxLayout(f);

    QGridLayout *serialComTableLayout = new QGridLayout();
    QLabel *serialComPaneltitle = new QLabel("Control Panel:");
    serialComPaneltitle->setStyleSheet("color: white;");
    st =new QPushButton("Connect");
    stop= new QPushButton("Disconnect");
    clear= new QPushButton("Clear");

    st->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    stop->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    clear->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    st->setFixedSize(150, 20);
    stop->setFixedSize(150, 20);
    clear->setFixedSize(150, 20);

    QLabel *label1 = new QLabel("Select a port:");
    label1->setStyleSheet("color: white;");
    // 2. Create a QComboBox for the first menu
    QList<QSerialPortInfo> serialPortInfos =  QSerialPortInfo::availablePorts();
    comboBox1 = new QComboBox();
    comboBox1->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        comboBox1->addItem(portInfo.portName());
    }
    QLabel *label2 = new QLabel("Select a buadrate:");
    label2->setStyleSheet("color: white;");
    // 2. Create a QComboBox for the first menu
    comboBox2 = new QComboBox();
    comboBox1->setFixedSize(150, 20);
    comboBox2->setFixedSize(150, 20);
    comboBox2->setStyleSheet("color: white;border: 2px solid #7DF9FF;");
    QList<QString> buadrateslist = {"9600", "19200", "38400", "57600","115200" };
    for (const QString rate : buadrateslist) {
        comboBox2->addItem(rate);
    }
    serialComTableLayout->addWidget(serialComPaneltitle,0,1);
    serialComTableLayout->addLayout(dataTableLayout,0,3,4,3);
    serialComTableLayout->addLayout(valvesTableLayout,0,6);
    serialComTableLayout->addLayout(commandButtonsTableLayout,0,7,4,2);
    serialComTableLayout->addWidget(label1,1,1);
    serialComTableLayout->addWidget(comboBox1,1,2);
    serialComTableLayout->addWidget(label2,2,1);
    serialComTableLayout->addWidget(comboBox2,2,2);
    serialComTableLayout->addWidget(st,3,1);
    serialComTableLayout->addWidget(clear,3,2);
    serialComTableLayout->addWidget(stop,4,1);
    controlPanelLayout->addLayout(serialComTableLayout);

    connect(st, &QPushButton::pressed, this, &MainWindow::displayData);
    connect(stop, &QPushButton::pressed, this, &MainWindow::stopDisplay);
    connect(clear,&QPushButton::pressed, this,  &MainWindow::Clear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayData()
{
    QString selectedPort = comboBox1->currentText();
    QString selectedBuadrate = comboBox2->currentText();
    worker2 = new workerreader(0,"/dev/"+selectedPort,selectedBuadrate,  &share_resource1);
    thread2 = new QThread(this);
    worker2->moveToThread(thread2);
    connect(thread2, &QThread::started, worker2, &workerreader::openSerialConnection);
    connect(thread2, &QThread::finished, worker2, &QObject::deleteLater);
    connect(thread2, &QThread::finished, thread2, &QObject::deleteLater);
    connect(open_PFill,&QPushButton::pressed,worker2,&workerreader::open_PFill_method);
    connect(close_PFill,&QPushButton::pressed,worker2,&workerreader::close_PFill_method);
    connect(open_POIV,&QPushButton::pressed,worker2,&workerreader::open_POIV_method);
    connect(close_POIV,&QPushButton::pressed,worker2,&workerreader::close_POIV_method);
    connect(open_OXIFill,&QPushButton::pressed,worker2,&workerreader::open_OXIFill_method);
    connect(close_OXIFill,&QPushButton::pressed,worker2,&workerreader::close_OXIFill_method);
    connect(launch, &QPushButton::pressed, worker2, &workerreader::launch_method);
    connect(abort, &QPushButton::pressed, worker2, &workerreader::abort_method);
    thread2->start();
    worker3 = new workerdisplay(1, &share_resource1);
    thread3 = new QThread(this);
    worker3->moveToThread(thread3);
    connect(thread3, &QThread::started, worker3, &workerdisplay::display);
    connect(thread3, &QThread::finished, worker3, &QObject::deleteLater);
    connect(thread3, &QThread::finished, thread3, &QObject::deleteLater);
    connect(worker3,&workerdisplay::updateDisplay,this, &MainWindow::handleUpdatedData);
    thread3->start();
    worker4 = new workersave(2,&share_resource1);
    thread4 = new QThread(this);
    worker4->moveToThread(thread4);
    connect(thread4, &QThread::started, worker4, &workersave::saveToCSV);
    connect(thread4, &QThread::finished, worker4, &QObject::deleteLater);
    connect(thread4, &QThread::finished, thread4, &QObject::deleteLater);
    thread4->start();
}

void MainWindow::stopDisplay()
{
    thread2->quit();
    thread2->wait();
    delete thread2;
    worker3->stop();
    thread3->quit();
    thread3->wait();
    delete thread3;
    worker4->stop();
    thread4->quit();
    thread4->wait();
    delete thread4;
}



void MainWindow::handleUpdatedData(vector<string> data)
{
    string mission_time = data[0];
    double time = std::stod(mission_time);
    double temp1 = std::stod(data[1]);
    double pressure1 = std::stod(data[3]);
    double temp2 = std::stod(data[2]);
    double pressure2 = std::stod(data[4]);
    double temp3 = std::stod(data[5]);
    double pressure3 = std::stod(data[7]);
    // Temperature Row
    l6->setText(QString::fromStdString(data[1]));
    l7->setText(QString::fromStdString(data[2]));
    // Pressure Row
    l10->setText(QString::fromStdString(data[3]));
    l8->setText(QString::fromStdString(data[5]));
    l11->setText(QString::fromStdString(data[4]));
    l12->setText(QString::fromStdString(data[7]));
    // Values open or close
    l19->setText(QString::fromStdString(data[13]));
    l20->setText(QString::fromStdString(data[14]));
    l21->setText(QString::fromStdString(data[15]));
    l22->setText(QString::fromStdString(data[16]));
    // Update plots
    series1->append(time,temp1 );
    series2->append(time,pressure1);
    series3->append(time,temp2 );
    series4->append(time,pressure2);
    series5->append(time,temp3 );
    series6->append(time,pressure3);
    if (time > 100.0) { // If X range exceeds a limit, scroll the view
        QValueAxis *axisX = qobject_cast<QValueAxis *>(series1->chart()->axes(Qt::Horizontal).first());
        axisX->setRange(time - 90, time + 10); // Keep a window of 100 points
        QValueAxis *axisX2 = qobject_cast<QValueAxis *>(series3->chart()->axes(Qt::Horizontal).first());
        axisX2->setRange(time - 90, time + 10); // Keep a window of 100 points
        QValueAxis *axisX3 = qobject_cast<QValueAxis *>(series5->chart()->axes(Qt::Horizontal).first());
        axisX3->setRange(time - 90, time + 10); // Keep a window of 100 points
    }
    chartView1->update();
    chartView2->update();
    chartView3->update();
}



void MainWindow::Clear()
{
    // Temperature Row
    l6->setText("0");
    l7->setText("0");
    l8->setText("0");
    // Pressure Row
    l10->setText("0");
    l11->setText("0");
    l12->setText("0");
    // Values open or close
    l19->setText("0");
    l20->setText("0");
    l21->setText("0");
    l22->setText("0");
    series1->clear();
    series2->clear();
    series3->clear();
    series4->clear();
    series5->clear();
    series6->clear();
}





































