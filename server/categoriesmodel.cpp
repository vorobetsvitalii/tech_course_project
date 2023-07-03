#include "categoriesmodel.h"

CategoriesModel::CategoriesModel(const std::string& name)
{
    setName(name);
}
CategoriesModel::CategoriesModel(const std::string& name, int id)
{
    setName(name);
    setId(id);
}

const QString CategoriesModel::GetTable() const
{
    return "Categories";
}

void CategoriesModel::InsertCategory()
{
    QString insertQuery = "INSERT INTO " + GetTable() + " (CategoryName) VALUES ('" + QString::fromStdString(this->getName()) + "')";
    Insert(insertQuery);
}
void CategoriesModel::SelectCategory()
{
    QString selectQuery = "SELECT * FROM " + GetTable();
    QString result = Select(selectQuery);
    std::cout << "Select Result: " << result.toStdString() << std::endl;
}
void CategoriesModel::UpdateCategory()
{
    QString updateQuery = "UPDATE " + GetTable() + " SET CategoryName='" + QString::fromStdString(this->getName()) + "' WHERE CategoryId=" + QString::number(this->getId());
    Update(updateQuery);
}

void CategoriesModel::DeleteCategory()
{
    QString deleteQuery = "DELETE FROM " + GetTable() + " WHERE CategoryId=" + QString::number(this->getId());
    Delete(deleteQuery);
}
