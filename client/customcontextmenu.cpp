#include "customcontextmenu.h"

CustomContextMenu::CustomContextMenu(QWidget *parent) : QMenu(parent)
{
    QAction *action1 = new QAction("Hide", this);
    QAction *action2 = new QAction("Delete", this);
    QAction *action3 = new QAction("Edit", this);

    connect(action1, &QAction::triggered, this, &CustomContextMenu::handleContextMenuAction);
    connect(action2, &QAction::triggered, this, &CustomContextMenu::handleContextMenuAction);
    connect(action3, &QAction::triggered, this, &CustomContextMenu::handleContextMenuAction);

    addAction(action1);
    addSeparator();
    addAction(action2);
    addSeparator();
    addAction(action3);

    this->setStyleSheet("font-size: 16px;"
                        "margin: 3px;"
                        "padding: 5px;"
                        "border: 1px solid #C4CED4;"
                        "background: white;"
                        "color: #333333;"
                        "font-size: 9pt;"
                        "font-weight: bold;"
                        "");
}

void CustomContextMenu::handleContextMenuRequested(const QPoint &pos)
{
    emit contextMenuRequested(pos);
}

void CustomContextMenu::handleContextMenuAction()
{
    QAction *senderAction = qobject_cast<QAction*>(sender());

    if (senderAction)
    {
        if (senderAction->text() == "Hide")
        {
            qDebug() << "Hide action triggered!";
        }
        else if (senderAction->text() == "Delete")
        {
            qDebug() << "Delete action triggered!";
        }
        else if (senderAction->text() == "Edit")
        {
            qDebug() << "Edit action triggered!";
        }
    }
}
