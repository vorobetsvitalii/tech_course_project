#ifndef TEAMMODEL_H
#define TEAMMODEL_H

#include "dbmodel.h"
#include "../common/model/team.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

class TeamModel: public DbModel , public team
{

public:
    virtual const QString GetTable() const override;
    void InsertTeam();
    void UpdateTeam();
    void DeleteTeam();
    QString SelectTeam();
    QString SelectLocations();

    static std::vector<team> SelectTeams();
    static void EditTeams(std::vector<TeamModel> items);
    static void DeleteTeams(std::vector<TeamModel> items);

    QJsonObject LocationJson(QString);

    TeamModel();
};

#endif // TEAMMODEL_H
