#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QString>
#include "../server/categoriesmodel.h"
#include <sstream>


using namespace testing;

class CategoriesModelSerDesTest: public testing::Test {
protected:
    CategoriesModel category;

    void SetUp() override {

        category.setId(1);
        category.setName("TestCategory");
    }
};

TEST_F(CategoriesModelSerDesTest, SerializeWithValidData) {
    QJsonObject jsonObject = category.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("CategoryName"));
    EXPECT_TRUE(jsonObject.contains("CategoryId"));

    EXPECT_EQ(jsonObject["CategoryId"].toInt(), category.getId());
    EXPECT_EQ(jsonObject["CategoryName"].toString().toStdString(), category.getName());
}
TEST_F(CategoriesModelSerDesTest, SerializeWithEmptyName) {
    category.setName("");

    // Serialize the object
    QJsonObject jsonObject = category.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("CategoryName"));
    EXPECT_TRUE(jsonObject.contains("CategoryId"));

    EXPECT_EQ(jsonObject["CategoryId"].toInt(), category.getId());
    EXPECT_EQ(jsonObject["CategoryName"].toString().toStdString(),category.getName());
}
TEST_F(CategoriesModelSerDesTest, SerializeWithSpecialCharactersInName) {
    category.setName("Test@Category");

    // Serialize the object
    QJsonObject jsonObject = category.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("CategoryName"));
    EXPECT_TRUE(jsonObject.contains("CategoryId"));

    EXPECT_EQ(jsonObject["CategoryId"].toInt(), category.getId());
    EXPECT_EQ(jsonObject["CategoryName"].toString().toStdString(), category.getName());
}


TEST_F(CategoriesModelSerDesTest, DeserializeWithValidData) {
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = "TestCategory";
    jsonObject["CategoryId"] = 1;

    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getId(), deserializedCategory.getId());
    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}
TEST_F(CategoriesModelSerDesTest, DeserializeWithEmptyName) {
    category.setName("");
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = "";
    jsonObject["CategoryId"] = 1;

    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getId(), deserializedCategory.getId());
    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}
/*TEST_F(CategoriesModelSerDesTest, DeserializeWithMissingKeys) {
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = "TestCategory";

    // 'CategoryId' key is missing
    CategoriesModel deserializedCategoryModel;
    deserializedCategoryModel.LoadJsonObject(jsonObject);
    EXPECT_EQ(deserializedCategoryModel.getId(),0);
    EXPECT_EQ(deserializedCategoryModel.getName(), "TestCategory");
}*/
TEST_F(CategoriesModelSerDesTest, DeserializeWithInvalidValue) {
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = "TestCategory";
    jsonObject["CategoryId"] = "InvalidValue";

    CategoriesModel deserializedCategoryModel;
    deserializedCategoryModel.LoadJsonObject(jsonObject);
    EXPECT_EQ(deserializedCategoryModel.getId(), 0);
    EXPECT_EQ(deserializedCategoryModel.getName(), "TestCategory");
}
TEST_F(CategoriesModelSerDesTest, DeserializeWithSpecialCharactersInName) {
    category.setName("Test@Category");
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = "Test@Category";
    jsonObject["CategoryId"] = 1;

    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getId(), deserializedCategory.getId());
    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}

//Combined tests
TEST_F(CategoriesModelSerDesTest, SerializeDeserializeWithValidData) {
    category.setId(42);

    // Serialize the object and then deserialize it
    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getId(), deserializedCategory.getId());
    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}

TEST_F(CategoriesModelSerDesTest, SerializeDeserializeWithMinId) {
    category.setId(std::numeric_limits<int>::min());

    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getId(), deserializedCategory.getId());
}

TEST_F(CategoriesModelSerDesTest, SerializeDeserializeWithMaxId) {
    category.setId(std::numeric_limits<int>::max());

    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getId(), deserializedCategory.getId());
}

TEST_F(CategoriesModelSerDesTest, SerializeDeserializeWithZeroId) {
    category.setId(0);

    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getId(), deserializedCategory.getId());
}

TEST_F(CategoriesModelSerDesTest, SerializeDeserializeWithEmptyName) {
    category.setName("");

    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}

TEST_F(CategoriesModelSerDesTest, SerializeDeserializeWithWhitespaceName) {
    category.setName("     ");

    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}


TEST_F(CategoriesModelSerDesTest, SerializeAndDeserializeArrayWithMultipleValidData) {
    CategoriesModel category1;
    category1.setId(1);
    category1.setName("Category1");

    CategoriesModel category2;
    category2.setId(2);
    category2.setName("Category2");

    // Create an array of CategoriesModel objects
    std::vector<CategoriesModel*> categoriesArray;
    categoriesArray.push_back(&category1);
    categoriesArray.push_back(&category2);

    // Serialize the array
    QJsonArray jsonArray;
    for (const auto& category : categoriesArray) {
        jsonArray.append(category->GetJsonObject());
    }

    EXPECT_EQ(jsonArray.size(), 2);

    QJsonObject jsonObject1 = jsonArray.at(0).toObject();
    EXPECT_TRUE(jsonObject1.contains("CategoryId"));
    EXPECT_TRUE(jsonObject1.contains("CategoryName"));

    EXPECT_EQ(jsonObject1["CategoryId"].toInt(), category1.getId());
    EXPECT_EQ(jsonObject1["CategoryName"].toString().toStdString(), category1.getName());

    QJsonObject jsonObject2 = jsonArray.at(1).toObject();
    EXPECT_TRUE(jsonObject2.contains("CategoryId"));
    EXPECT_TRUE(jsonObject2.contains("CategoryName"));

    EXPECT_EQ(jsonObject2["CategoryId"].toInt(), category2.getId());
    EXPECT_EQ(jsonObject2["CategoryName"].toString().toStdString(), category2.getName());

    // Deserialize the array
    std::vector<CategoriesModel> deserializedCategories;
    for (const auto& json : jsonArray) {
        QJsonObject categoryJsonObject = json.toObject();
        CategoriesModel deserializedCategory;
        deserializedCategory.LoadJsonObject(categoryJsonObject);
        deserializedCategories.push_back(deserializedCategory);
    }

    EXPECT_EQ(deserializedCategories.size(), 2);

    EXPECT_EQ(deserializedCategories[0].getId(), 1);
    EXPECT_EQ(deserializedCategories[0].getName(), "Category1");

    EXPECT_EQ(deserializedCategories[1].getId(), 2);
    EXPECT_EQ(deserializedCategories[1].getName(), "Category2");
}
