#ifndef MY_VIEW_H
#define MY_VIEW_H

#include <QChartView>
#include<QtCharts>
#include <QWidget>
#include<QDebug>

class my_view : public QChartView
{
protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
public:
    my_view(QWidget* parent = nullptr);
private:
    QPoint m_lastMousePos;
};

#endif // MY_VIEW_H
