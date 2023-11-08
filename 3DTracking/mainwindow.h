#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include<MyPoint.h>
#include<virtualPoint.h>
#include<rectPoint.h>
#include<spherPoint.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
public:
    QList<virtualPoint*> newPoints;
    QChart* xy_chart;
    QChart* xz_chart;
    QChart* zy_chart;
    QChart* rphi_chart;
    QChart* rteta_chart;
    void addPointToSeries(double x, double y, QLineSeries* series);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initializeChart(QChart*,QString,QString,QString);
    void addSeriesToChart(QChart*,QLineSeries*);
    void CreatingCharts();
    void readDataFromFile(QString);

private slots:
    void tooltip(QPointF point,QLineSeries *);

    void on_startBtn_clicked();

    void on_XoYAxisYslider_valueChanged(int value);

    void on_XoYaxisYslider_valueChanged(int value);

    void on_XoZAxisYslider_valueChanged(int value);

    void on_XoZAxisXslider_valueChanged(int value);

    void on_ZoYAxisYslider_valueChanged(int value);

    void on_ZoYAxisXslider_valueChanged(int value);

    void on_RoPhiAxisYSlider_valueChanged(int value);

    void on_RoPhiAxisXSlider_valueChanged(int value);

    void on_RoTetaAxisYSlider_valueChanged(int value);

    void on_RoTetaAxisXSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
