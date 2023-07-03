#include "category.h"
void Category::LoadJsonObject(QJsonObject obj)
{
    if (obj.contains("CategoryName"))
    {
        name = obj["CategoryName"].toString().toStdString();
    }

    if (obj.contains("CategoryId"))
    {
        id = obj["CategoryId"].toInt();
    }
}

QJsonObject Category::GetJsonObject()
{
    QJsonObject jsonObject;
    jsonObject["CategoryName"] = QString::fromStdString(name);
    return jsonObject;
}

int Category::getId() const
{
    return id;
}

std::string Category::getName() const
{
    return name;
}

void Category::setName(std::string name)
{
    this->name = name;
}

std::ostream& operator<<(std::ostream& os, const Category& category)
{
    os << "Category ID: " << category.getId() << ", Name: " << category.getName();
    return os;
}
