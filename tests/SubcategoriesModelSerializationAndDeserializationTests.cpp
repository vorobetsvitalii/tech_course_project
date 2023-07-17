#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QString>
#include "../server/subcategoryModel.h"
#include <sstream>
#include <vector>

using namespace testing;

class SubcategoriesModelSerDesTest: public testing::Test {
protected:
    SubcategoriesModel subcategory;

    void SetUp() override {

        subcategory.setId(1);
        subcategory.setName("TestSubcategory");
        subcategory.setCategoryId(18);
    }
};

TEST_F(SubcategoriesModelSerDesTest, SerializeWithValidData) {
    QJsonObject jsonObject = subcategory.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryName"));
    EXPECT_TRUE(jsonObject.contains("CategoryId"));

    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), subcategory.getId());
    EXPECT_EQ(jsonObject["SubcategoryName"].toString().toStdString(), subcategory.getName());
    EXPECT_EQ(jsonObject["CategoryId"].toInt(), subcategory.getCategoryId());
}
TEST_F(SubcategoriesModelSerDesTest, SerializeWithEmptyName) {
    subcategory.setName("");

    // Serialize the object
    QJsonObject jsonObject = subcategory.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryName"));
    EXPECT_TRUE(jsonObject.contains("CategoryId"));

    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), subcategory.getId());
    EXPECT_EQ(jsonObject["SubcategoryName"].toString().toStdString(), subcategory.getName());
    EXPECT_EQ(jsonObject["CategoryId"].toInt(), subcategory.getCategoryId());
}
TEST_F(SubcategoriesModelSerDesTest, SerializeWithSpecialCharactersInName) {
    subcategory.setName("Test@Category");

    // Serialize the object
    QJsonObject jsonObject = subcategory.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject.contains("SubcategoryName"));
    EXPECT_TRUE(jsonObject.contains("CategoryId"));

    EXPECT_EQ(jsonObject["SubcategoryId"].toInt(), subcategory.getId());
    EXPECT_EQ(jsonObject["SubcategoryName"].toString().toStdString(), subcategory.getName());
    EXPECT_EQ(jsonObject["CategoryId"].toInt(), subcategory.getCategoryId());
}

TEST_F(SubcategoriesModelSerDesTest, DeserializeWithValidData) {
    QJsonObject jsonObject;
    jsonObject["SubcategoryName"] = "TestSubcategory";
    jsonObject["SubcategoryId"] = 1;
    jsonObject["CategoryId"] = 18;

    // Deserialize the object
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(subcategory.getId(), deserializedSubcategory.getId());
    EXPECT_EQ(subcategory.getName(), deserializedSubcategory.getName());
    EXPECT_EQ(subcategory.getCategoryId(), deserializedSubcategory.getCategoryId());
}
TEST_F(SubcategoriesModelSerDesTest, DeserializeWithEmptyName) {
    subcategory.setName("");
    QJsonObject jsonObject;
    jsonObject["SubcategoryName"] = "";
    jsonObject["SubcategoryId"] = 1;
    jsonObject["CategoryId"] = 18;

    // Deserialize the object
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(subcategory.getId(), deserializedSubcategory.getId());
    EXPECT_EQ(subcategory.getName(), deserializedSubcategory.getName());
    EXPECT_EQ(subcategory.getCategoryId(), deserializedSubcategory.getCategoryId());
}
/*TEST_F(SubcategoriesModelSerDesTest, DeserializeWithMissingKeys) {
    QJsonObject jsonObject;
    jsonObject["SubcategoryName"] = "TestSubcategory";
    jsonObject["CategoryId"] = 18;


    // 'SubCategoryId' key is missing
    // Deserialize the object
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(deserializedSubcategory.getId(),0);
    EXPECT_EQ(deserializedSubcategory.getName(), subcategory.getName());
    EXPECT_EQ( deserializedSubcategory.getCategoryId(),subcategory.getCategoryId());
}*/
TEST_F(SubcategoriesModelSerDesTest, DeserializeWithInvalidValue) {
    QJsonObject jsonObject;
    jsonObject["SubcategoryName"] = "TestSubcategory";
    jsonObject["SubcategoryId"] = "InvalidValue"; // Non-integer value
    jsonObject["CategoryId"] = 18;

    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(deserializedSubcategory.getId(),0);
    EXPECT_EQ(deserializedSubcategory.getName(), subcategory.getName());
    EXPECT_EQ( deserializedSubcategory.getCategoryId(),subcategory.getCategoryId());
}
TEST_F(SubcategoriesModelSerDesTest, DeserializeWithSpecialCharactersInName) {
    subcategory.setName("Test@Category");
    QJsonObject jsonObject;
    jsonObject["SubcategoryName"] = "Test@Category";
    jsonObject["SubcategoryId"] = 1;
    jsonObject["CategoryId"] = 18;

    // Deserialize the object
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(subcategory.getId(), deserializedSubcategory.getId());
    EXPECT_EQ(subcategory.getName(), deserializedSubcategory.getName());
    EXPECT_EQ(subcategory.getCategoryId(), deserializedSubcategory.getCategoryId());
}

//Combined tests
TEST_F(SubcategoriesModelSerDesTest, SerializeDeserializeWithValidData) {
    subcategory.setId(42);

    // Serialize the object and then deserialize it
    QJsonObject jsonObject = subcategory.GetJsonObject();
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(subcategory.getId(), deserializedSubcategory.getId());
    EXPECT_EQ(subcategory.getName(), deserializedSubcategory.getName());
    EXPECT_EQ( subcategory.getCategoryId(),deserializedSubcategory.getCategoryId());
}
TEST_F(SubcategoriesModelSerDesTest, SerializeDeserializeWithMinId) {
    subcategory.setId(std::numeric_limits<int>::min());

    QJsonObject jsonObject = subcategory.GetJsonObject();
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);


    EXPECT_EQ(subcategory.getId(), deserializedSubcategory.getId());
}
TEST_F(SubcategoriesModelSerDesTest, SerializeDeserializeWithMaxId) {
    subcategory.setId(std::numeric_limits<int>::max());

    QJsonObject jsonObject = subcategory.GetJsonObject();
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(subcategory.getId(), deserializedSubcategory.getId());
}
TEST_F(SubcategoriesModelSerDesTest, SerializeDeserializeWithZeroId) {
    subcategory.setId(0);

    QJsonObject jsonObject = subcategory.GetJsonObject();
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(subcategory.getId(), deserializedSubcategory.getId());
}
TEST_F(SubcategoriesModelSerDesTest, SerializeDeserializeWithEmptyName) {
    subcategory.setName("");

    QJsonObject jsonObject = subcategory.GetJsonObject();
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(subcategory.getName(), deserializedSubcategory.getName());
}
TEST_F(SubcategoriesModelSerDesTest, SerializeDeserializeWithWhitespaceName) {
    subcategory.setName("     ");

    QJsonObject jsonObject = subcategory.GetJsonObject();
    SubcategoriesModel deserializedSubcategory;
    deserializedSubcategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(subcategory.getName(), deserializedSubcategory.getName());
}


TEST_F(SubcategoriesModelSerDesTest, SerializeArrayWithMultipleValidData) {
    // Create an array of SubcategoriesModel objects
    std::vector<SubcategoriesModel*> subcategoriesArray;

    SubcategoriesModel subcategory1;
    subcategory1.setId(1);
    subcategory1.setName("Subcategory1");
    subcategory1.setCategoryId(18);

    SubcategoriesModel subcategory2;
    subcategory2.setId(2);
    subcategory2.setName("Subcategory2");
    subcategory2.setCategoryId(18);

    subcategoriesArray.push_back(&subcategory1);
    subcategoriesArray.push_back(&subcategory2);

    // Serialize the array
    QJsonArray jsonArray;
    for (const auto& sub : subcategoriesArray) {
        jsonArray.append(sub->GetJsonObject());
    }

    EXPECT_EQ(jsonArray.size(), 2);

    QJsonObject jsonObject1 = jsonArray.at(0).toObject();
    EXPECT_TRUE(jsonObject1.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject1.contains("SubcategoryName"));
    EXPECT_TRUE(jsonObject1.contains("CategoryId"));

    EXPECT_EQ(jsonObject1["SubcategoryId"].toInt(), subcategory1.getId());
    EXPECT_EQ(jsonObject1["SubcategoryName"].toString().toStdString(), subcategory1.getName());
    EXPECT_EQ(jsonObject1["CategoryId"].toInt(), subcategory1.getCategoryId());

    QJsonObject jsonObject2 = jsonArray.at(1).toObject();
    EXPECT_TRUE(jsonObject2.contains("SubcategoryId"));
    EXPECT_TRUE(jsonObject2.contains("SubcategoryName"));
    EXPECT_TRUE(jsonObject2.contains("CategoryId"));

    EXPECT_EQ(jsonObject2["SubcategoryId"].toInt(), subcategory2.getId());
    EXPECT_EQ(jsonObject2["SubcategoryName"].toString().toStdString(), subcategory2.getName());
    EXPECT_EQ(jsonObject2["CategoryId"].toInt(), subcategory2.getCategoryId());
}
TEST_F(SubcategoriesModelSerDesTest, DeserializeArrayWithMultipleValidData) {
    // Create an array of JSON objects
    QJsonArray jsonArray;

    QJsonObject jsonObject1;
    jsonObject1["SubcategoryName"] = "Subcategory1";
    jsonObject1["SubcategoryId"] = 1;
    jsonObject1["CategoryId"] = 18;
    jsonArray.append(jsonObject1);

    QJsonObject jsonObject2;
    jsonObject2["SubcategoryName"] = "Subcategory2";
    jsonObject2["SubcategoryId"] = 2;
    jsonObject2["CategoryId"] = 18;
    jsonArray.append(jsonObject2);

    // Deserialize the array
    std::vector<SubcategoriesModel> deserializedSubcategories;
    for (const auto& json : jsonArray) {
        QJsonObject subJsonObject = json.toObject();
        SubcategoriesModel deserializedSubcategory;
        deserializedSubcategory.LoadJsonObject(subJsonObject);
        deserializedSubcategories.push_back(deserializedSubcategory);
    }

    EXPECT_EQ(deserializedSubcategories.size(), 2);

    EXPECT_EQ(deserializedSubcategories[0].getId(), 1);
    EXPECT_EQ(deserializedSubcategories[0].getName(), "Subcategory1");
    EXPECT_EQ(deserializedSubcategories[0].getCategoryId(), 18);

    EXPECT_EQ(deserializedSubcategories[1].getId(), 2);
    EXPECT_EQ(deserializedSubcategories[1].getName(), "Subcategory2");
    EXPECT_EQ(deserializedSubcategories[1].getCategoryId(), 18);
}
