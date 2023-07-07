#include "subcategory.h"

void Subcategory::LoadJsonObject(QJsonObject obj)
{
    if (obj.contains("SubcategoryName"))
    {
        name = obj["SubcategoryName"].toString().toStdString();
    }

    if (obj.contains("SubcategoryId"))
    {
        id = obj["SubcategoryId"].toInt();
    }

    if (obj.contains("CategoryId"))
    {
        categoryId = obj["CategoryId"].toInt();
    }
}

QJsonObject Subcategory::GetJsonObject()
{
    QJsonObject jsonObject;
    jsonObject["SubcategoryName"] = QString::fromStdString(name);
    jsonObject["SubcategoryId"] = id;
    jsonObject["CategoryId"] = categoryId;
    return jsonObject;
}

int Subcategory::getId() const
{
    return id;
}

int Subcategory::getCategoryId() const
{
    return categoryId;
}

std::string Subcategory::getName() const
{
    return name;
}

void Subcategory::setId(int id)
{
    this->id = id;
}

void Subcategory::setCategoryId(int categoryId)
{
    this->categoryId = categoryId;
}
void Subcategory::setName(std::string name)
{
    this->name = name;
}

std::ostream& operator<<(std::ostream& os, const Subcategory& subcategory)
{
    os << "Subcategory ID: " << subcategory.getId() << ", Name: " << subcategory.getName() << "Ccategory ID: " << subcategory.getId();
    return os;
}
