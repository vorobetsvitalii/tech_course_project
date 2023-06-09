#include "teammodel.h"
const QString TeamModel::GetTable() const
{
    return "Teams";
}

void TeamModel::InsertTeam()
{
    QString subQuery =QString("SELECT COALESCE(MAX(TeamId), 0) + 1 FROM %1").arg(this->GetTable());


    //QByteArray byteArray = QByteArray::fromBase64(this->getTeamLogoBlob().toLatin1());
    QString insertQuery = QString("SET IDENTITY_INSERT %1 ON;INSERT INTO %1 (TeamId, TeamName, SubcategoryId, TeamLocation, TeamLogo) "
                                  "VALUES ((%2), '%3', '%4', '%5', CAST('%6' AS VARBINARY(MAX)))")
                              .arg(this->GetTable())
                              .arg(subQuery)
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


std::vector<team> TeamModel::SelectTeam()
{
    std::unique_ptr<TeamModel> TM = std::make_unique<TeamModel>();

    QString IdSelect = QString("SELECT TeamId FROM %1").arg(TM->GetTable());

    std::vector<team>TeamVector;


    QRegularExpression regexID(R"(\s*,\s*)");

    // Розділення рядка за допомогою регулярного виразу


    QString IdResult = TM->Select(IdSelect);
    QStringList teamIdTokens = IdResult.split(regexID);

    // Виведення результату
    for (const QString& teamId : teamIdTokens) {


    QString selectQuery = QString("SELECT * FROM %1 WHERE TeamId = %2").arg(TM->GetTable()).arg(teamId);
    QString result = TM->Select(selectQuery);
    qDebug() << result;
    QRegularExpression regex(R"((.*?), (.*?), (.*?), (.*?), (.*))");

    // Використовуємо QRegularExpressionMatchIterator для знаходження всіх входжень, що відповідають регулярному виразу
    QRegularExpressionMatchIterator regexIterator = regex.globalMatch(result);

    // Перебираємо всі знайдені входження
    while (regexIterator.hasNext()) {
        QRegularExpressionMatch match = regexIterator.next();

        // Отримуємо значення полів за номерами груп
        QString teamId = match.captured(1);
        QString teamName = match.captured(2);
        QString subcategoryId = match.captured(3);
        QString teamLocation = match.captured(4);
        QString teamLogo = match.captured(5);



        // Створюємо новий екземпляр Team і додаємо його до вектора
        team Team;
        Team.setTeamId(teamId.toInt());
        Team.setTeamName(teamName);
        Team.setSubcategoryId(subcategoryId.toInt());
        Team.setTeamLocation(teamLocation.toInt());
        Team.setTeamLogoBlob(teamLogo);
        TeamVector.push_back(Team);
    }
    }
    return TeamVector;
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
