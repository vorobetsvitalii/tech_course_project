#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QString>
#include "../server/teammodel.h"
#include "qjsonarray.h"
#include <sstream>

using namespace testing;

class TeamModelSerDesTest : public testing::Test {
protected:
    TeamModel teamModel;


    void SetUp() override {
        // Set up the test case with valid data
        teamModel.setTeamId(1);
        teamModel.setTeamName("Team1");
        teamModel.setSubcategoryId(18);
        teamModel.setTeamLocation(42);
        teamModel.setTeamLogoBlob("TeamLogoBlob");
    }
};
TEST_F(TeamModelSerDesTest, SerializeWithValidData) {
    // Serialize the team object
    QJsonObject jsonObject = teamModel.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("TeamId"));
    EXPECT_TRUE(jsonObject.contains("TeamName"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("TeamLocation"));
    EXPECT_TRUE(jsonObject.contains("TeamLogoBlob"));

    EXPECT_EQ(jsonObject["TeamId"].toInt(), teamModel.getTeamId());
    EXPECT_EQ(jsonObject["TeamName"].toString().toStdString(), teamModel.getTeamName().toStdString());
    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), teamModel.getSubcategoryId());
    EXPECT_EQ(jsonObject["TeamLocation"].toInt(), teamModel.getTeamLocation());
    EXPECT_EQ(jsonObject["TeamLogoBlob"].toString().toStdString(), teamModel.getTeamLogoBlob().toStdString());
}
TEST_F(TeamModelSerDesTest, SerializeWithEmptyName) {
    teamModel.setTeamName("");

    // Serialize the object
    QJsonObject jsonObject = teamModel.GetJsonObject();


    EXPECT_TRUE(jsonObject.contains("TeamId"));
    EXPECT_TRUE(jsonObject.contains("TeamName"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("TeamLocation"));
    EXPECT_TRUE(jsonObject.contains("TeamLogoBlob"));

    EXPECT_EQ(jsonObject["TeamId"].toInt(), teamModel.getTeamId());
    EXPECT_EQ(jsonObject["TeamName"].toString().toStdString(), teamModel.getTeamName().toStdString());
    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), teamModel.getSubcategoryId());
    EXPECT_EQ(jsonObject["TeamLocation"].toInt(), teamModel.getTeamLocation());
    EXPECT_EQ(jsonObject["TeamLogoBlob"].toString().toStdString(), teamModel.getTeamLogoBlob().toStdString());
}
TEST_F(TeamModelSerDesTest, SerializeWithSpecialCharactersInName) {
    teamModel.setTeamName("Team@Name");

    // Serialize the object
    QJsonObject jsonObject = teamModel.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("TeamId"));
    EXPECT_TRUE(jsonObject.contains("TeamName"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("TeamLocation"));
    EXPECT_TRUE(jsonObject.contains("TeamLogoBlob"));

    EXPECT_EQ(jsonObject["TeamId"].toInt(), teamModel.getTeamId());
    EXPECT_EQ(jsonObject["TeamName"].toString().toStdString(), teamModel.getTeamName().toStdString());
    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), teamModel.getSubcategoryId());
    EXPECT_EQ(jsonObject["TeamLocation"].toInt(), teamModel.getTeamLocation());
    EXPECT_EQ(jsonObject["TeamLogoBlob"].toString().toStdString(), teamModel.getTeamLogoBlob().toStdString());
}
TEST_F(TeamModelSerDesTest, SerializeWithEmptyLogoBlob) {
    teamModel.setTeamLogoBlob(""); // Empty Logo Blob

    // Serialize the team object
    QJsonObject jsonObject = teamModel.GetJsonObject();

    // Check if the JSON object has the expected keys and values
    EXPECT_TRUE(jsonObject.contains("TeamId"));
    EXPECT_TRUE(jsonObject.contains("TeamName"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("TeamLocation"));
    EXPECT_TRUE(jsonObject.contains("TeamLogoBlob"));

    EXPECT_EQ(jsonObject["TeamId"].toInt(), teamModel.getTeamId());
    EXPECT_EQ(jsonObject["TeamName"].toString().toStdString(), teamModel.getTeamName().toStdString());
    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), teamModel.getSubcategoryId());
    EXPECT_EQ(jsonObject["TeamLocation"].toInt(), teamModel.getTeamLocation());
    EXPECT_EQ(jsonObject["TeamLogoBlob"].toString().toStdString(), "");
}

TEST_F(TeamModelSerDesTest, DeserializeWithValidData) {
    QJsonObject jsonObject;
    jsonObject["TeamName"] = "Team1";
    jsonObject["TeamId"] = 1;
    jsonObject["SubcategoryId"] = 18;
    jsonObject["TeamLocation"] = 42;
    jsonObject["TeamLogoBlob"] = "TeamLogoBlob";

    // Deserialize the object
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamId(), deserializedTeamModel.getTeamId());
    EXPECT_EQ(teamModel.getTeamName(), deserializedTeamModel.getTeamName());
    EXPECT_EQ(teamModel.getSubcategoryId(), deserializedTeamModel.getSubcategoryId());
    EXPECT_EQ(teamModel.getTeamLocation(), deserializedTeamModel.getTeamLocation());
    EXPECT_EQ(teamModel.getTeamLogoBlob(), deserializedTeamModel.getTeamLogoBlob());
}
TEST_F(TeamModelSerDesTest, DeserializeWithEmptyName) {
    teamModel.setTeamName("");
    QJsonObject jsonObject;
    jsonObject["TeamName"] = "";
    jsonObject["TeamId"] = 1;
    jsonObject["SubcategoryId"] = 18;
    jsonObject["TeamLocation"] = 42;
    jsonObject["TeamLogoBlob"] = "TeamLogoBlob";

    // Deserialize the object
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    // Check if the deserialized object matches the original object
    EXPECT_EQ(teamModel.getTeamId(), deserializedTeamModel.getTeamId());
    EXPECT_EQ(teamModel.getTeamName(), deserializedTeamModel.getTeamName());
    EXPECT_EQ(teamModel.getSubcategoryId(), deserializedTeamModel.getSubcategoryId());
    EXPECT_EQ(teamModel.getTeamLocation(), deserializedTeamModel.getTeamLocation());
    EXPECT_EQ(teamModel.getTeamLogoBlob(), deserializedTeamModel.getTeamLogoBlob());
}
TEST_F(TeamModelSerDesTest, DeserializeWithInvalidValue) {
    QJsonObject jsonObject;
    jsonObject["TeamName"] = "Team1";
    jsonObject["TeamId"] = "InvalidValue"; // Non-integer value
    jsonObject["SubcategoryId"] = 18;
    jsonObject["TeamLocation"] = 42;
    jsonObject["TeamLogoBlob"] = "TeamLogoBlob";

    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(deserializedTeamModel.getTeamId(), 0); // Default value should be used
    EXPECT_EQ(deserializedTeamModel.getTeamName(), teamModel.getTeamName());
    EXPECT_EQ(deserializedTeamModel.getSubcategoryId(),teamModel.getSubcategoryId());
    EXPECT_EQ(deserializedTeamModel.getTeamLocation(), teamModel.getTeamLocation());
    EXPECT_EQ(deserializedTeamModel.getTeamLogoBlob(), teamModel.getTeamLogoBlob());
}
TEST_F(TeamModelSerDesTest, DeserializeWithSpecialCharactersInName) {
    teamModel.setTeamName("Test@Name");
    QJsonObject jsonObject;
    jsonObject["TeamName"] = teamModel.getTeamName();
    jsonObject["TeamId"] = 1;
    jsonObject["SubcategoryId"] = 18;
    jsonObject["TeamLocation"] = 42;
    jsonObject["TeamLogoBlob"] = "TeamLogoBlob";

    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(deserializedTeamModel.getTeamId(), 1);
    EXPECT_EQ(deserializedTeamModel.getTeamName().toStdString(), teamModel.getTeamName().toStdString());
    EXPECT_EQ(deserializedTeamModel.getSubcategoryId(), teamModel.getSubcategoryId());
    EXPECT_EQ(deserializedTeamModel.getTeamLocation(), teamModel.getTeamLocation());
    EXPECT_EQ(deserializedTeamModel.getTeamLogoBlob(), teamModel.getTeamLogoBlob());
}
TEST_F(TeamModelSerDesTest, DeserializeWithEmptyLogoBlob) {
    teamModel.setTeamLogoBlob("");
    QJsonObject jsonObject;
    jsonObject["TeamName"] = "Team1";
    jsonObject["TeamId"] = 1;
    jsonObject["SubcategoryId"] = 18;
    jsonObject["TeamLocation"] = 42;
    jsonObject["TeamLogoBlob"] = ""; // Empty Logo Blob

    // Deserialize the team object
    TeamModel deserializedTeam;
    deserializedTeam.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamId(), deserializedTeam.getTeamId());
    EXPECT_EQ(teamModel.getTeamName(), deserializedTeam.getTeamName());
    EXPECT_EQ(teamModel.getSubcategoryId(), deserializedTeam.getSubcategoryId());
    EXPECT_EQ(teamModel.getTeamLocation(), deserializedTeam.getTeamLocation());
    EXPECT_EQ(teamModel.getTeamLogoBlob(), deserializedTeam.getTeamLogoBlob());
}

//combined
TEST_F(TeamModelSerDesTest, SerializeDeserializeWithValidData) {
    teamModel.setTeamId(42);

    // Serialize the object and then deserialize it
    QJsonObject jsonObject = teamModel.GetJsonObject();
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    // Check if the deserialized object matches the original object
    EXPECT_EQ(teamModel.getTeamId(), deserializedTeamModel.getTeamId());
    EXPECT_EQ(teamModel.getTeamName(), deserializedTeamModel.getTeamName());
    EXPECT_EQ(teamModel.getSubcategoryId(), deserializedTeamModel.getSubcategoryId());
    EXPECT_EQ(teamModel.getTeamLocation(), deserializedTeamModel.getTeamLocation());
    EXPECT_EQ(teamModel.getTeamLogoBlob(), deserializedTeamModel.getTeamLogoBlob());
}

TEST_F(TeamModelSerDesTest, SerializeDeserializeWithMinId) {
    teamModel.setTeamId(std::numeric_limits<int>::min());

    QJsonObject jsonObject = teamModel.GetJsonObject();
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamId(), deserializedTeamModel.getTeamId());
}

TEST_F(TeamModelSerDesTest, SerializeDeserializeWithMaxId) {
    teamModel.setTeamId(std::numeric_limits<int>::max());

    QJsonObject jsonObject = teamModel.GetJsonObject();
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamId(), deserializedTeamModel.getTeamId());
}

TEST_F(TeamModelSerDesTest, SerializeDeserializeWithZeroId) {
    teamModel.setTeamId(0);

    QJsonObject jsonObject = teamModel.GetJsonObject();
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamId(), deserializedTeamModel.getTeamId());
}

TEST_F(TeamModelSerDesTest, SerializeDeserializeWithEmptyName) {
    teamModel.setTeamName("");

    QJsonObject jsonObject = teamModel.GetJsonObject();
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamName(), deserializedTeamModel.getTeamName());
}

TEST_F(TeamModelSerDesTest, SerializeDeserializeWithWhitespaceName) {
    teamModel.setTeamName("     ");

    QJsonObject jsonObject = teamModel.GetJsonObject();
    TeamModel deserializedTeamModel;
    deserializedTeamModel.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamName(), deserializedTeamModel.getTeamName());
}

TEST_F(TeamModelSerDesTest, SerializeDeserializeWithSpecialCharactersInName) {
    teamModel.setTeamName("Test@Team"); // Name with special characters

    // Serialize the team object
    QJsonObject jsonObject = teamModel.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("TeamId"));
    EXPECT_TRUE(jsonObject.contains("TeamName"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("TeamLocation"));
    EXPECT_TRUE(jsonObject.contains("TeamLogoBlob"));

    EXPECT_EQ(jsonObject["TeamId"].toInt(), teamModel.getTeamId());
    EXPECT_EQ(jsonObject["TeamName"].toString().toStdString(), teamModel.getTeamName().toStdString());
    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), teamModel.getSubcategoryId());
    EXPECT_EQ(jsonObject["TeamLocation"].toInt(), teamModel.getTeamLocation());
    EXPECT_EQ(jsonObject["TeamLogoBlob"].toString().toStdString(), teamModel.getTeamLogoBlob().toStdString());

    // Deserialize the team object
    TeamModel deserializedTeam;
    deserializedTeam.LoadJsonObject(jsonObject);

    EXPECT_EQ(teamModel.getTeamId(), deserializedTeam.getTeamId());
    EXPECT_EQ(teamModel.getTeamName(), deserializedTeam.getTeamName());
    EXPECT_EQ(teamModel.getSubcategoryId(), deserializedTeam.getSubcategoryId());
    EXPECT_EQ(teamModel.getTeamLocation(), deserializedTeam.getTeamLocation());
    EXPECT_EQ(teamModel.getTeamLogoBlob(), deserializedTeam.getTeamLogoBlob());
}


TEST_F(TeamModelSerDesTest, SerializeAndDeserializeArrayWithMultipleValidData) {
    TeamModel team1;
    team1.setTeamId(1);
    team1.setTeamName("Team1");
    team1.setSubcategoryId(18);
    team1.setTeamLocation(42);
    team1.setTeamLogoBlob("TeamLogoBlob1");

    TeamModel team2;
    team2.setTeamId(2);
    team2.setTeamName("Team2");
    team2.setSubcategoryId(18);
    team2.setTeamLocation(42);
    team2.setTeamLogoBlob("TeamLogoBlob2");

    // Create an array of TeamModel objects
    std::vector<TeamModel*> teamsArray;
    teamsArray.push_back(&team1);
    teamsArray.push_back(&team2);

    // Serialize the array
    QJsonArray jsonArray;
    for (const auto& team : teamsArray) {
        jsonArray.append(team->GetJsonObject());
    }

    EXPECT_EQ(jsonArray.size(), 2);

    QJsonObject jsonObject1 = jsonArray.at(0).toObject();
    EXPECT_TRUE(jsonObject1.contains("TeamId"));
    EXPECT_TRUE(jsonObject1.contains("TeamName"));
    EXPECT_TRUE(jsonObject1.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject1.contains("TeamLocation"));
    EXPECT_TRUE(jsonObject1.contains("TeamLogoBlob"));

    EXPECT_EQ(jsonObject1["TeamId"].toInt(), team1.getTeamId());
    EXPECT_EQ(jsonObject1["TeamName"].toString().toStdString(), team1.getTeamName().toStdString());
    EXPECT_EQ(jsonObject1["SubcategoryId"].toInt(), team1.getSubcategoryId());
    EXPECT_EQ(jsonObject1["TeamLocation"].toInt(), team1.getTeamLocation());
    EXPECT_EQ(jsonObject1["TeamLogoBlob"].toString().toStdString(), team1.getTeamLogoBlob().toStdString());

    QJsonObject jsonObject2 = jsonArray.at(1).toObject();
    EXPECT_TRUE(jsonObject2.contains("TeamId"));
    EXPECT_TRUE(jsonObject2.contains("TeamName"));
    EXPECT_TRUE(jsonObject2.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject2.contains("TeamLocation"));
    EXPECT_TRUE(jsonObject2.contains("TeamLogoBlob"));

    EXPECT_EQ(jsonObject2["TeamId"].toInt(), team2.getTeamId());
    EXPECT_EQ(jsonObject2["TeamName"].toString().toStdString(), team2.getTeamName().toStdString());
    EXPECT_EQ(jsonObject2["SubcategoryId"].toInt(), team2.getSubcategoryId());
    EXPECT_EQ(jsonObject2["TeamLocation"].toInt(), team2.getTeamLocation());
    EXPECT_EQ(jsonObject2["TeamLogoBlob"].toString().toStdString(), team2.getTeamLogoBlob().toStdString());

    // Deserialize the array
    std::vector<TeamModel> deserializedTeams;
    for (const auto& json : jsonArray) {
        QJsonObject teamJsonObject = json.toObject();
        TeamModel deserializedTeam;
        deserializedTeam.LoadJsonObject(teamJsonObject);
        deserializedTeams.push_back(deserializedTeam);
    }

    EXPECT_EQ(deserializedTeams.size(), 2);

    EXPECT_EQ(deserializedTeams[0].getTeamId(),team1.getTeamId());
    EXPECT_EQ(deserializedTeams[0].getTeamName(), team1.getTeamName());
    EXPECT_EQ(deserializedTeams[0].getSubcategoryId(), team1.getSubcategoryId());
    EXPECT_EQ(deserializedTeams[0].getTeamLocation(), team1.getTeamLocation());
    EXPECT_EQ(deserializedTeams[0].getTeamLogoBlob(), team1.getTeamLogoBlob());

    EXPECT_EQ(deserializedTeams[1].getTeamId(), team2.getTeamId());
    EXPECT_EQ(deserializedTeams[1].getTeamName(),  team2.getTeamName());
    EXPECT_EQ(deserializedTeams[1].getSubcategoryId(), team2.getSubcategoryId());
    EXPECT_EQ(deserializedTeams[1].getTeamLocation(),team2.getTeamLocation());
    EXPECT_EQ(deserializedTeams[1].getTeamLogoBlob(), team2.getTeamLogoBlob());
}






