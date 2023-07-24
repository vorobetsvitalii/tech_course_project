#ifndef RESIZABLEWIDGET_H
#define RESIZABLEWIDGET_H

#include <QWidget>
#include "tableWidget.h"

class ResizableWidget : public QWidget
{
    Q_OBJECT

public:
    ResizableWidget(QWidget* parent = nullptr);

    void resize();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    const int minWidth = 700;
    void showEvent(QShowEvent* event);

signals:
    void resizableWidgetResized();


};

#endif // RESIZABLEWIDGET_H
