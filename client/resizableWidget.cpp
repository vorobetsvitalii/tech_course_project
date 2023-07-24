#include "resizablewidget.h"

ResizableWidget::ResizableWidget(QWidget* parent) : QWidget(parent) {}

void ResizableWidget::resize()
{
    int width = minWidth > parentWidget()->width() ? minWidth : parentWidget()->width();
    setFixedWidth(width);
}

void ResizableWidget::resizeEvent(QResizeEvent *event)
{
    emit resizableWidgetResized();
    qDebug() << "resizableWidget Resized";

    QWidget::resizeEvent(event);
}


void ResizableWidget::showEvent(QShowEvent* event)
{
    qDebug() << "showEvent ResizableWidget";
    QWidget::showEvent(event);
    resize();
}
