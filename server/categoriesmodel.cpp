#include "categoriesmodel.h"

CategoriesModel::CategoriesModel() {}

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

void CategoriesModel::UpdateCategory()
{
    QString updateQuery = "UPDATE " + GetTable() + " SET CategoryName='" + QString::fromStdString(this->getName()) + "' WHERE CategoryId=" + QString::number(this->getId());
    Update(updateQuery);
    qDebug() << "Category Model updated!";
}

void CategoriesModel::DeleteCategory()
{
    QString deleteQuery = "DELETE FROM " + GetTable() + " WHERE CategoryId=" + QString::number(this->getId());
    Delete(deleteQuery);
}

std::vector<Category> CategoriesModel::SelectCategory()
{
    std::unique_ptr<CategoriesModel> cm = std::make_unique<CategoriesModel>();
    QString selectQuery = "SELECT * FROM " + cm->GetTable();
    QString result = cm->Select(selectQuery);
    std::cout << "Select Result: " << result.toStdString() << std::endl;

    std::vector<Category> categoryVector;
    QStringList dataVector = result.split(", ");

    for (int i = 0; i < dataVector.size(); i += 2) {
        int categoryId = dataVector[i].toInt();
        QString categoryName = dataVector[i + 1];

        Category category;
        category.setId(categoryId);
        category.setName(categoryName.toStdString());

        categoryVector.push_back(category);
    }
    return categoryVector;

}

void CategoriesModel::EditCategories(std::vector<CategoriesModel> items)
{
    for(CategoriesModel& c : items)
    {
        c.UpdateCategory();
    }
}

void CategoriesModel::DeleteCategories(std::vector<CategoriesModel> items)
{
    for(CategoriesModel& c : items)
    {
        c.DeleteCategory();
    }
}
