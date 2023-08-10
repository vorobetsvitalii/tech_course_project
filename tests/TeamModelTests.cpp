#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TeamModelMock.h"
#include "../server/teammodel.h"

using namespace testing;


bool compareTeams(const Team& team1, const Team& team2) {
    return team1.getTeamId() == team2.getTeamId() &&
           team1.getTeamName() == team2.getTeamName() &&
           team1.getDate() == team2.getDate() &&
           team1.getSubcategoryId() == team2.getSubcategoryId() &&
           team1.getTeamLocation() == team2.getTeamLocation() &&
           team1.getTeamLogoBlob() == team2.getTeamLogoBlob();
}

TEST(TeamModelTest, SelectTeamsMultipleTeamsTest) {


    TeamModelMock teamModelMock;

    std::vector<Team> expectedTeams;

    Team team1;
    team1.setTeamId(1);
    team1.setTeamName("Team1");
    expectedTeams.push_back(team1);

    Team team2;
    team2.setTeamId(2);
    team2.setTeamName("Team2");
    expectedTeams.push_back(team2);

    Team team3;
    team3.setTeamId(3);
    team3.setTeamName("Team3");
    expectedTeams.push_back(team3);

    EXPECT_CALL(teamModelMock, SelectTeams())
        .WillOnce(Return(expectedTeams));

    std::vector<Team> result = teamModelMock.SelectTeams();
    for (auto & tmp:result){
        std::cout<<tmp.getTeamName().toStdString();
    }

    ASSERT_EQ(result.size(), expectedTeams.size());
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_TRUE(compareTeams(result[i], expectedTeams[i]));
    }
}


TEST(TeamModelTest, SelectTeamsEmptyTest) {
    TeamModelMock teamModelMock;

    std::vector<Team> expectedTeams;


    EXPECT_CALL(teamModelMock, SelectTeams())
        .WillOnce(Return(expectedTeams));


    std::vector<Team> result = teamModelMock.SelectTeams();


    ASSERT_TRUE(result.empty());
}

TEST(TeamModelTest, SelectTeamsSingleTeamTest) {
    TeamModelMock teamModelMock;

    std::vector<Team> expectedTeams;

    Team team1;
    team1.setTeamId(1);
    team1.setTeamName("Team1");
    expectedTeams.push_back(team1);

    EXPECT_CALL(teamModelMock, SelectTeams())
        .WillOnce(Return(expectedTeams));

    std::vector<Team> result = teamModelMock.SelectTeams();

    ASSERT_EQ(result.size(), expectedTeams.size());
    ASSERT_TRUE(compareTeams(result[0], expectedTeams[0]));
}


TEST(TeamModelTest, UpdateTeamTest) {
    TeamModelMock teamModelMock;


    Team updatedTeam;
    updatedTeam.setTeamId(1);
    updatedTeam.setTeamName("UpdatedTeam");


    EXPECT_CALL(teamModelMock, UpdateTeam())
        .WillOnce(Return(true));


    bool result = teamModelMock.UpdateTeam();


    ASSERT_TRUE(result);
}
