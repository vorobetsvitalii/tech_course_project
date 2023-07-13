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
    QString SelectTeam();
    QString SelectLocations();

    QJsonObject LocationJson(QString);

    TeamModel();
};

#endif // TEAMMODEL_H
