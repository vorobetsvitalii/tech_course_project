#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QString>
#include <sstream>
#include <vector>
//#include "../client/client.h"

using namespace testing;

class ServerTest: public testing::Test {
public:
    void SetUp() override{

    }
};


TEST(ServerTest, GetSubcategoriesTest) {
    //std::vector<Subcategory> subcategories = Client::GetSubcategories();

    // Перевірка, чи отримано підкатегорії
    //EXPECT_FALSE();
}
