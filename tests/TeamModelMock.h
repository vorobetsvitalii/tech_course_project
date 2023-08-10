#ifndef TEAMMODELMOCK_H
#define TEAMMODELMOCK_H

#include "gmock/gmock.h" // Включення бібліотеки Google Mock
#include "../server/teammodel.h"   // Ваш оригінальний клас

class TeamModelMock : public TeamModel
{
public:
    MOCK_METHOD(void, InsertTeam, ());
    MOCK_METHOD(bool, UpdateTeam, ());
    MOCK_METHOD(void, DeleteTeam, ());
    MOCK_METHOD(std::vector<Team>, SelectTeams, ());
    MOCK_METHOD(QString, SelectLocations, ());
    MOCK_METHOD(void, EditTeams, (std::vector<TeamModel>));
    MOCK_METHOD(void, DeleteTeams, (std::vector<TeamModel>));
    MOCK_METHOD(QJsonObject, LocationJson, (QString));
};


#endif // TEAMMODELMOCK_H
