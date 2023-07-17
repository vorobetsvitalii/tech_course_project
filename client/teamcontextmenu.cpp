#include "teamcontextmenu.h"
#include "qpushbutton.h"

TeamContextMenu::TeamContextMenu(QWidget *parent)  : QMenu(parent)
{
    QAction *action1 = new QAction("Hide", this);
    QAction *action2 = new QAction("Delete", this);
    QAction *action3 = new QAction("Edit", this);

    connect(action1, &QAction::triggered, this, &TeamContextMenu::handleContextMenuAction);
    connect(action2, &QAction::triggered, this, &TeamContextMenu::handleContextMenuAction);
    connect(action3, &QAction::triggered, this, &TeamContextMenu::handleContextMenuAction);

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

void TeamContextMenu::setTeamIndex(const int &index_)
{
    index = index_;
}

void TeamContextMenu::setTempTeamButton(QPushButton* temp_team_button_)
{
    temp_team_button = temp_team_button_;
}

void TeamContextMenu::handleContextMenuRequested(const QPoint &pos)
{
    emit contextMenuRequested(pos);
}

void TeamContextMenu::handleContextMenuAction()
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
            if(temp_team_button != nullptr)
            {

            }
        }
        else if (senderAction->text() == "Edit")
        {

        }
    }
}

QPushButton* TeamContextMenu::temp_team_button = nullptr;
int TeamContextMenu::index = NULL;
