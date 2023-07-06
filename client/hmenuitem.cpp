#include "hmenuitem.h"
#include <QEvent>

HMenuItem::HMenuItem(Category* category)
{
    this->category = category;
    this->setStyleSheet("font: 700 14px \"Open Sans\";\
                         padding-top: 14px; padding-bottom: 13px; \
                         padding-left: 8px; padding-right: 8px; \
                         color: #B2B2B2;"
                        "border: none;");
    this->setText(QString::fromStdString(category->getName()));
    this->setCursor(Qt::PointingHandCursor);
    this->setMaximumWidth(this->width());

    this->installEventFilter(this);

    this->state = std::unique_ptr<QLabel>(new QLabel("hidden", this));
    state->setStyleSheet("background-color: #EDEDED;"
                         "color: #B2B2B2;"
                         "font: 600 8px \"Open Sans\";"
                         "border-radius: 6px;"
                         "padding-top: 0.5px; padding-bottom: 0.5px;"
                         "padding-left: 6px; padding-right: 6px;");
    state->move(this->width() - state->width(), 3);
    isHidden = false;

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
        if(event->type() == QEvent::Show || event->type() == QEvent::Resize) {
            if(!isHidden) state->hide();
            state->move(this->width() - state->width(), 3);
        }
    }
    return false;
}

void HMenuItem::setHidden(bool isHidden) {
    this->isHidden = isHidden;
    if(isHidden) {
        state->show();
        state->move(this->width() - state->width(), 3);
    }
    else state->hide();
}

Category* HMenuItem::getCategory() {
    return category;
}
