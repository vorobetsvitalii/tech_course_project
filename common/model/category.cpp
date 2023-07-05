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
    jsonObject["CategoryId"] = id;
    return jsonObject;
}

QJsonObject Category::GetJsonObject(const QString& categories) {
    QStringList dataList = categories.split(", ");
    QJsonArray categoriesArray;
    for (int i = 0; i < dataList.size(); i += 2) {
        int categoryId = dataList[i].toInt();
        QString categoryName = dataList[i + 1];

        QJsonObject categoryObject;
        categoryObject["CategoryId"] = categoryId;
        categoryObject["CategoryName"] = categoryName;

        categoriesArray.append(categoryObject);
    }

    QJsonObject jsonObject;
    jsonObject["categories"] = categoriesArray;

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
void Category::setId(int id)
{
    this->id = id;
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
