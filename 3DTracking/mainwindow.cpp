#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
#include<QDebug>
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xy_chart = new QChart;
    initializeChart(xy_chart,"XoY","Ось X","Ось Y");

    xz_chart = new QChart;
    initializeChart(xz_chart,"XoZ","Ось X","Ось Z");

    zy_chart = new QChart;
    initializeChart(zy_chart,"ZoY","Ось Z","Ось Y");

    rphi_chart = new QChart;
    initializeChart(rphi_chart,"RoPhi","Phi","R");

    rteta_chart = new QChart;
    initializeChart(rteta_chart,"RoTeta","Teta","R");

    ui->xy_view->setChart(xy_chart);

    ui->xz_view->setChart(xz_chart);

    ui->zy_view->setChart(zy_chart);

    ui->rphi_view->setChart(rphi_chart);

    ui->rteta_view->setChart(rteta_chart);

    ui->textEdit->setText("Координаты точки");
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tooltip(QPointF pos,QLineSeries *series)
{
    int index = -1;
    qreal distance = std::numeric_limits<qreal>::max();
    for (int i = 0; i < series->count(); i++) {
        QPointF point = series->at(i);
        qreal d = qSqrt(qPow(point.x() - pos.x(), 2.0) + qPow(point.y() - pos.y(), 2.0));
        if (d < distance) {
            index = i;
            distance = d;
        }
    }
    double pi = acos(-1.0);
    ui->textEdit->setText(QString("t: %1\nКоординаты точки в декартовой системе:\nX: %2 \nY: %3\nZ: %4\n"
                                  "Координаты точки в сферической системе:\nR: %5\nφ: %6°\nθ: %7°\n")
                          .arg(newPoints[index]->getT())
                          .arg(newPoints[index]->getX()).arg(newPoints[index]->getY())
                          .arg(newPoints[index]->getZ()).arg(newPoints[index]->getR())
                          .arg((newPoints[index]->getPhi()*180)/pi).arg((newPoints[index]->getTeta()*180)/pi));
}
void MainWindow::CreatingCharts(){
    QLineSeries* xy_series = new QLineSeries();
    QLineSeries* xz_series = new QLineSeries();
    QLineSeries* zy_series = new QLineSeries();
    QLineSeries* rphi_series = new QLineSeries();
    QLineSeries* rteta_series = new QLineSeries();
    qSort(newPoints.begin(),newPoints.end(),[](const virtualPoint* a, const virtualPoint* b) -> bool {return a->getT() < b->getT();});
    for (int i = 0; i < newPoints.size();i++){
        addPointToSeries(newPoints[i]->getX(),newPoints[i]->getZ(),xz_series);
        addPointToSeries(newPoints[i]->getX(),newPoints[i]->getY(),xy_series);
        addPointToSeries(newPoints[i]->getZ(),newPoints[i]->getY(),zy_series);
        addPointToSeries(newPoints[i]->getPhi(),newPoints[i]->getR(),rphi_series);
        addPointToSeries(newPoints[i]->getTeta(),newPoints[i]->getR(),rteta_series);
    }
    addSeriesToChart(xy_chart,xy_series);
    addSeriesToChart(xz_chart,xz_series);
    addSeriesToChart(zy_chart,zy_series);
    addSeriesToChart(rphi_chart,rphi_series);
    addSeriesToChart(rteta_chart,rteta_series);
}
void MainWindow::initializeChart(QChart* chart,QString title,QString axisXtitle,QString axisYtitle){
    chart->legend()->hide();
    chart->setTitle(title);
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText(axisXtitle);
    axisX->setRange(-10, 10);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(axisYtitle);
    axisY->setRange(-10, 10);
    chart->addAxis(axisY, Qt::AlignLeft);
}
void MainWindow::addPointToSeries(double x, double y, QLineSeries *series){
    series->append(x,y);
}
void MainWindow::addSeriesToChart(QChart* chart,QLineSeries *series){
    if (chart->series().count() != 0){
        chart->removeAllSeries();
    }
    series->setPointsVisible(true);
    chart->addSeries(series);
    series->attachAxis(chart->axes(Qt::Vertical).at(0));
    series->attachAxis(chart->axes(Qt::Horizontal).at(0));
    connect(series, &QLineSeries::clicked, std::bind(&MainWindow::tooltip, this, std::placeholders::_1, series));
}
void MainWindow::readDataFromFile(QString fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    if (newPoints.size() != 0) newPoints.clear();
    QString format = in.readLine();
    if (format == "#rect") {
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parameters = line.split(" ");
            newPoints.append(new rectPoint(parameters[0].toDouble(),parameters[1].toDouble(),parameters[2].toDouble(),parameters[3].toDouble()));
        }
    }
    else if (format == "#spher"){
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parameters = line.split(" ");
            newPoints.append(new spherPoint(parameters[0].toDouble(),parameters[1].toDouble(),parameters[2].toDouble(),parameters[3].toDouble()));
        }
    }
    else return;
    CreatingCharts();
    file.close();
}

void MainWindow::on_startBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"),"",tr("Text Files (*.txt)"));
    if(!fileName.isEmpty()){
        readDataFromFile(fileName);
    }
}


void MainWindow::on_XoYAxisYslider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(xy_chart->axes(Qt::Vertical).at(0))->setTickCount(value);
}


void MainWindow::on_XoYaxisYslider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(xy_chart->axes(Qt::Horizontal).at(0))->setTickCount(value);
}


void MainWindow::on_XoZAxisYslider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(xz_chart->axes(Qt::Vertical).at(0))->setTickCount(value);
}


void MainWindow::on_XoZAxisXslider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(xz_chart->axes(Qt::Horizontal).at(0))->setTickCount(value);
}


void MainWindow::on_ZoYAxisYslider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(zy_chart->axes(Qt::Vertical).at(0))->setTickCount(value);

}


void MainWindow::on_ZoYAxisXslider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(zy_chart->axes(Qt::Horizontal).at(0))->setTickCount(value);
}


void MainWindow::on_RoPhiAxisYSlider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(rphi_chart->axes(Qt::Horizontal).at(0))->setTickCount(value);
}


void MainWindow::on_RoPhiAxisXSlider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(rphi_chart->axes(Qt::Horizontal).at(0))->setTickCount(value);
}


void MainWindow::on_RoTetaAxisYSlider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(rteta_chart->axes(Qt::Horizontal).at(0))->setTickCount(value);
}


void MainWindow::on_RoTetaAxisXSlider_valueChanged(int value)
{
    qobject_cast<QValueAxis*>(rteta_chart->axes(Qt::Horizontal).at(0))->setTickCount(value);
}

