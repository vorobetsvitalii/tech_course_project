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

void TeamModel::UpdateTeam()
{
    QString updateQuery = "UPDATE " + GetTable() + " SET TeamName='" + this->getTeamName() + "', SubcategoryId="
                          + QString::number(this->getSubcategoryId()) + ", TeamLocation=" + QString::number(this->getTeamLocation()) +
                          ", TeamLogo='" + this->getTeamLogoBlob() + "' WHERE TeamId=" + QString::number(this->getTeamId());
    Update(updateQuery);
}

void TeamModel::DeleteTeam()
{
    QString deleteQuery = "DELETE FROM " + GetTable() + " WHERE TeamId=" + QString::number(this->getTeamId());
    Delete(deleteQuery);
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

std::vector<team> TeamModel::SelectTeams()
{
    std::unique_ptr<TeamModel> tm = std::make_unique<TeamModel>();
    QString selectQuery = "SELECT TeamId, TeamName, SubcategoryId, TeamLocation, TeamLogo FROM " + tm->GetTable();
    QString result = tm->Select(selectQuery);

    std::vector<team> items;
    QStringList dataVector = result.split(", ");
    for(int i = 0; i < dataVector.count(); i += 5)
    {
        team t = TeamModel();
        t.setTeamId(dataVector[i].toInt());
        t.setTeamName(dataVector[i+1]);
        t.setSubcategoryId(dataVector[i+2].toInt());
        t.setTeamLocation(dataVector[i+3].toInt());
        t.setTeamLogoBlob(dataVector[i+4]);
        items.push_back(t);

    }

    return items;

}

void TeamModel::EditTeams(std::vector<TeamModel> items)
{
    for(TeamModel& t : items)
    {
        t.UpdateTeam();
    }
}

void TeamModel::DeleteTeams(std::vector<TeamModel> items)
{
    for(TeamModel& t : items)
    {
        t.DeleteTeam();
    }
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
