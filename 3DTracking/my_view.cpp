#include "my_view.h"

my_view::my_view(QWidget* parent):QChartView(parent)
{

}
void my_view::wheelEvent(QWheelEvent* event){
    QPointF point = chart()->mapToValue(event->pos());
    if (event->angleDelta().y() > 0){
        auto xAxis = qobject_cast<QValueAxis*>(chart()->axes(Qt::Horizontal).at(0));
        auto yAxis = qobject_cast<QValueAxis*>(chart()->axes(Qt::Vertical).at(0));
        if (std::abs(xAxis->max() - xAxis->min()) <=3 || std::abs(yAxis->max() - yAxis->min()) <=3){
            return;
        }
        qreal xsize = (std::abs(point.x() - xAxis->min()))/(std::abs(xAxis->max() -xAxis->min()));
        qreal ysize = (std::abs(point.y() - yAxis->min()))/(std::abs(yAxis->max() -yAxis->min()));
        xAxis->setRange(xAxis->min()+ xsize,xAxis->max() -(1-xsize));
        yAxis->setRange(yAxis->min()+ysize,yAxis->max() -(1-ysize));
    }
    else{
        auto xAxis = qobject_cast<QValueAxis*>(chart()->axes(Qt::Vertical).at(0));
        auto yAxis = qobject_cast<QValueAxis*>(chart()->axes(Qt::Horizontal).at(0));
        qreal xsize = (std::abs(point.x() - xAxis->min()))/(std::abs(xAxis->max() -xAxis->min()));
        qreal ysize = (std::abs(point.y() - yAxis->min()))/(std::abs(yAxis->max() -yAxis->min()));
        xAxis->setRange(xAxis->min()-(1-xsize),xAxis->max() + xsize);
        yAxis->setRange(yAxis->min()-(1-ysize),yAxis->max() + ysize);
    }
    QChartView::wheelEvent(event);
}
void my_view::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::RightButton)
    {
        qreal deltaX = event->pos().x() - m_lastMousePos.x();
        qreal deltaY = event->pos().y() - m_lastMousePos.y();

        auto xAxis = qobject_cast<QValueAxis*>(chart()->axes(Qt::Horizontal).at(0));
        auto yAxis = qobject_cast<QValueAxis*>(chart()->axes(Qt::Vertical).at(0));

        xAxis->setRange(xAxis->min() - deltaX/15, xAxis->max() - deltaX/15);
        yAxis->setRange(yAxis->min() + deltaY/15, yAxis->max() + deltaY/15);

        m_lastMousePos = event->pos();
    }
    QChartView::mouseMoveEvent(event);
}
void my_view::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton)
    {
        m_lastMousePos = event->pos();
    }
    QChartView::mousePressEvent(event);
}
