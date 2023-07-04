#include "hmenuitem.h"
#include <QEvent>

HMenuItem::HMenuItem(Category* category)
{
    this->category = category;
    this->setStyleSheet("font: 700 14px \"Open Sans\";\
                         padding-top: 14px; padding-bottom: 13px; \
                         padding-left: 5px; padding-right: 5px; \
                         color: #B2B2B2; "
                        "border: none;");
    this->setText(QString::fromStdString(category->getName()));
    this->setCursor(Qt::PointingHandCursor);
    this->setMaximumWidth(this->width());

    this->installEventFilter(this);

    this->state = new QLabel("hidden", this);
    state->setStyleSheet("background-color: #EDEDED;"
                         "color: #B2B2B2;"
                         "font: 600 8px \"Open Sans\";"
                         "border: none;"
                         "border-radius: 15px;"
                         "padding-top: 1px; padding-bottom: 1px;"
                         "padding-left: 5px; padding-right: 5px;"
                         "subcontrol-position: right center;"
                         "margin-top: 5px;");
    state->hide();

}

bool HMenuItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            this->setStyleSheet(this->styleSheet().replace("color: #B2B2B2;", "color: #7F7B7B;"));
            return true;
        }
        if(event->type() == QEvent::HoverLeave)
        {
            this->setStyleSheet(this->styleSheet().replace("color: #7F7B7B;", "color: #B2B2B2;"));
            return true;
        }
        if(event->type() == QEvent::MouseButtonRelease)
        {
            emit itemSelected(this);
            return true;
        }
    }
    return false;
}

Category* HMenuItem::getCategory() {
    return category;
}
