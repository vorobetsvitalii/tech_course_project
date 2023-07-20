#ifndef TEAMMODEL_H
#define TEAMMODEL_H

#include "dbmodel.h"
#include "../common/model/team.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QBuffer>
#include <QImage>
#include <regex>
#include <sstream>
#include <string>

class TeamModel: public DbModel , public Team
{

public:
    virtual const QString GetTable() const override;
    void InsertTeam();

    void UpdateTeam();
    void DeleteTeam();

    static std::vector<Team> SelectTeams();

    QString SelectLocations();


    static void EditTeams(std::vector<TeamModel> items);
    static void DeleteTeams(std::vector<TeamModel> items);

    QJsonObject LocationJson(QString);

    TeamModel();
};

#endif // TEAMMODEL_H
