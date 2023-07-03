#ifndef HMENUITEM_H
#define HMENUITEM_H

#include <string>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include "category.h"

class HMenuItem : public QPushButton
{
    Q_OBJECT
public:
    HMenuItem(Category* category);
    Category* getCategory();

private:
    Category* category;
    QLabel* state;

    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void itemSelected(HMenuItem* item);

};

#endif // HMENUITEM_H
