#include "teammodel.h"

const QString TeamModel::GetTable() const
{
    return "Teams";
}

void TeamModel::InsertTeam()
{
    QString insertQuery = QString("INSERT INTO %1 (TeamId, TeamName, SubcategoryId, TeamLocation, TeamLogo) "
                                  "VALUES ('%2', '%3', '%4', '%5', '%6')")
                              .arg(this->GetTable())
                              .arg(this->getTeamId())
                              .arg(this->getTeamName())
                              .arg(this->getSubcategoryId())
                              .arg(this->getTeamLocation())
                              .arg(this->getTeamLogoBlob());

    qDebug() << insertQuery;
    this->Insert(insertQuery);
}

QString TeamModel::SelectTeam()
{
    QString selectQuery = QString("SELECT * FROM %1").arg(this->GetTable());
    qDebug() << selectQuery;



    QString result = this->Select(selectQuery);
    qDebug() << result;
    return result;
}

QString TeamModel::SelectLocations()
{
    QString selectQuery = QString("SELECT * FROM Locations");

    QString result = this->Select(selectQuery);
    qDebug() << result;
    return result;
}

QJsonObject TeamModel::LocationJson(QString str)
{
    QJsonObject jsonObject;

    QRegularExpression regex("(\\d+), ([\\w ]+)");
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(str);

    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        QString key = match.captured(1);
        QString value = match.captured(2);
        jsonObject[key] = value;
    }

    return jsonObject;
}

TeamModel::TeamModel()
{

}
