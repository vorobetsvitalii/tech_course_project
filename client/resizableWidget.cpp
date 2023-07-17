#include "resizablewidget.h"

ResizableWidget::ResizableWidget(QWidget* parent) : QWidget(parent) {}

void ResizableWidget::resize()
{
    int width = minWidth > parentWidget()->width() ? minWidth : parentWidget()->width();
    setFixedWidth(width);
}
