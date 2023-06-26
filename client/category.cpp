#include "category.h"
Category Category::fromJSON(const std::string& json)
{
    Category category;

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(json);
    Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

    if (object->has("CategoryId"))
    {
        category.id = object->get("CategoryId").convert<int>();
    }

    if (object->has("CategoryName"))
    {
        category.name = object->get("CategoryName").convert<std::string>();
    }

    return category;
}

int Category::getId() const
{
    return id;
}

std::string Category::getName() const
{
    return name;
}

std::ostream& operator<<(std::ostream& os, const Category& category)
{
    os << "Category ID: " << category.getId() << ", Name: " << category.getName();
    return os;
}
