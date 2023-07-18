#ifndef TEAMCONTEXTMENU_H
#define TEAMCONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include <QPushButton>

#include "../common/model/team.h"
#include "client.h"
#include "deletepopup.h"
#include "editpopup.h"

class TeamContextMenu  : public QMenu
{
    Q_OBJECT

public:
    explicit TeamContextMenu(QWidget *parent = nullptr);

    static void setTeamIndex(const int& index_);
    static void setTempTeamButton(QPushButton* temp_team_button_);

    void onTeamNameUpdated(const QString& newName);
private:
    static QPushButton* temp_team_button;

    std::vector<team> teamsList;

    static int index;

signals:
    void contextMenuRequested(const QPoint &pos);

public slots:
    void handleContextMenuRequested(const QPoint &pos);

private slots:
    void handleContextMenuAction();
};

#endif // TEAMCONTEXTMENU_H
