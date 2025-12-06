#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineSeries>
#include <QChartView>
#include <QGridLayout>
#include <qlabel.h>
#include <QLineEdit>
#include <QComboBox>
#include <QThread>
#include "workerreader.h"
#include "workerdisplay.h"
#include "workersave.h"
#include <QMutex>
#include <QtCharts>
#include "sharedresource.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Charts
    QLineSeries *series1;
    QLineSeries *series2;
    QLineSeries *series3;
    QLineSeries *series4;
    QLineSeries *series5;
    QLineSeries *series6;
    QChart *chart1;
    QChart *chart2;
    QChart *chart3;
    QChart *chart4;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QValueAxis *axisY2;
    QValueAxis *axisX2;
    QValueAxis *axY2;
    QValueAxis *aY2;
    QValueAxis *axisX3;
    QValueAxis *alY2;
    QValueAxis *a2;
    QChartView *chartView1;
    QChartView *chartView2;
    QChartView *chartView3;
    QSize *s;
    // Layouts
    QGridLayout *gridLayout;
    QGridLayout *dataTableLayout;
    QGridLayout *valvesTableLayout;
    QGridLayout *commandButtonsTableLayout;
    QHBoxLayout *controlPanelLayout;
    // Frames
    QFrame *f;
    // Labels
    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QLabel *l4;
    QLabel *l5;
    QLabel *l6;
    QLabel *l7;
    QLabel *l8;
    QLabel *l9;
    QLabel *l10;
    QLabel *l11;
    QLabel *l12;
    // Values on/off indicators
    QLabel *l13;
    QLabel *l14;
    QLabel *l15;
    QLabel *l16;
    QLabel *l17;
    QLabel *l18;
    QLabel *l19;
    QLabel *l20;
    QLabel *l21;
    QLabel *l22;
    //Buttons
    QPushButton *open_PFill;
    QPushButton *close_PFill;
    QPushButton *open_POIV;
    QPushButton *close_POIV;
    QPushButton *open_OXIFill;
    QPushButton *close_OXIFill;
    QPushButton *launch;
    QPushButton *abort;
    QLabel *label1;
    QLabel *label2;
    QPushButton *st;
    QPushButton *clear;
    QPushButton *stop;
    QComboBox *comboBox1;
    QComboBox *comboBox2;
    workerreader *worker2;
    workerdisplay *worker3;
    workersave *worker4;
    QThread* thread2;
    QThread* thread3;
    QThread* thread4;
    sharedResource share_resource1;

public slots:
   void displayData();
   void stopDisplay();
   void handleUpdatedData(vector<string> data);
   void Clear();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
