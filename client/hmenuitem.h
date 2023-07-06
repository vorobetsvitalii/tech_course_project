#ifndef HMENUITEM_H
#define HMENUITEM_H

#include <string>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include "../common/model/category.h"

class HMenuItem : public QPushButton
{
    Q_OBJECT
public:
    HMenuItem(Category* category);
    Category* getCategory();
    void setHidden(bool isHidden);

private:
    Category* category;
    std::unique_ptr<QLabel> state;
    bool isHidden;

    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void itemSelected(HMenuItem* item);

};

#endif // HMENUITEM_H
