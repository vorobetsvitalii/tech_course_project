#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QString>
#include "../server/categoriesmodel.h"
#include <sstream>


using namespace testing;

class CategorySerializationTest : public testing::Test {
protected:
    CategoriesModel category;

    void SetUp() override {

        category.setId(1);
        category.setName("Test Category");
    }
};

TEST_F(CategorySerializationTest, SerializationTests) {
    QJsonObject jsonObject = category.GetJsonObject();

    EXPECT_TRUE(jsonObject.contains("CategoryName"));
    EXPECT_TRUE(jsonObject.contains("CategoryId"));

    EXPECT_EQ(jsonObject["CategoryName"].toString().toStdString(), category.getName());
    EXPECT_EQ(jsonObject["CategoryId"].toInt(), category.getId());
}

TEST_F(CategorySerializationTest, SerializeDeserializeWithValidData) {
    category.setId(42);
    category.setName("TestCategory");

    // Serialize the object and then deserialize it
    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);

    // Check if the deserialized object matches the original object
    EXPECT_EQ(category.getId(), deserializedCategory.getId());
    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}

TEST_F(CategorySerializationTest, SerializeDeserializeWithEdgeIdCases) {
    // Test minimum id value
    category.setId(std::numeric_limits<int>::min());
    category.setName("Category1");
    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(category.getId(), deserializedCategory.getId());

    // Test maximum id value
    category.setId(std::numeric_limits<int>::max());
    category.setName("Category2");
    jsonObject = category.GetJsonObject();
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(category.getId(), deserializedCategory.getId());

    // Test negative id value
    category.setId(-12345);
    category.setName("Category3");
    jsonObject = category.GetJsonObject();
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(category.getId(), deserializedCategory.getId());

    // Test zero id value
    category.setId(0);
    category.setName("Category4");
    jsonObject = category.GetJsonObject();
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(category.getId(), deserializedCategory.getId());
}

TEST_F(CategorySerializationTest, SerializeDeserializeWithEdgeNameCases) {
    // Test empty name
    category.setId(1);
    category.setName("");
    QJsonObject jsonObject = category.GetJsonObject();
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(category.getName(), deserializedCategory.getName());

    // Test whitespace-only name
    category.setId(2);
    category.setName("     ");
    jsonObject = category.GetJsonObject();
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(category.getName(), deserializedCategory.getName());
}

/*TEST_F(CategorySerializationTest, DeserializeMissingKeys) {
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = "TestCategory";

    // 'CategoryId' key is missing
    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(deserializedCategory.getId(), NULL); // Default value should be used
    EXPECT_EQ(deserializedCategory.getName(), "TestCategory");
}*/

TEST_F(CategorySerializationTest, DeserializeInvalidValue) {
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = "TestCategory";
    jsonObject["CategoryId"] = "InvalidValue"; // Non-integer value

    Category deserializedCategory;
    deserializedCategory.LoadJsonObject(jsonObject);
    EXPECT_EQ(deserializedCategory.getId(), 0); // Default value should be used
    EXPECT_EQ(deserializedCategory.getName(), "TestCategory");
}
