#ifndef RESIZABLEWIDGET_H
#define RESIZABLEWIDGET_H

#include <QWidget>

class ResizableWidget : public QWidget
{
    Q_OBJECT

public:
    ResizableWidget(QWidget* parent = nullptr);

    void resize();

private:
    const int minWidth = 700;
};

#endif // RESIZABLEWIDGET_H
