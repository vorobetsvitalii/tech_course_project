#include "subcategoryModel.h"

SubcategoriesModel::SubcategoriesModel() {}

SubcategoriesModel::SubcategoriesModel(const std::string& name)
{
    setName(name);
}
SubcategoriesModel::SubcategoriesModel(const std::string& name, int id)
{
    setName(name);
    setId(id);
}

SubcategoriesModel::SubcategoriesModel(const std::string& name, int id, int categoryId)
{
    setName(name);
    setId(id);
    setCategoryId(categoryId);
}

const QString SubcategoriesModel::GetTable() const
{
    return "Subcategories";
}

void SubcategoriesModel::InsertSubcategory()
{
    QString insertQuery = "INSERT INTO " + GetTable() + " (SubcategoryName, CategoryID) "
                          "VALUES ('" + QString::fromStdString(this->getName()) + "', " + QString::number(this->getCategoryId()) + ")";
    qDebug() << insertQuery;
    Insert(insertQuery);
}


void SubcategoriesModel::UpdateSubcategory()
{
    QString updateQuery = "UPDATE " + GetTable() + " SET SubcategoryName='" + QString::fromStdString(this->getName()) + "', CategoryID=" + QString::number(this->getCategoryId()) + " WHERE SubcategoryId=" + QString::number(this->getId());
    Update(updateQuery);
}

void SubcategoriesModel::DeleteSubcategory()
{
    QString deleteQuery = "DELETE FROM " + GetTable() + " WHERE SubcategoryId=" + QString::number(this->getId());
    Delete(deleteQuery);
}

std::vector<Subcategory> SubcategoriesModel::SelectSubcategory()
{
    std::unique_ptr<SubcategoriesModel> cm = std::make_unique<SubcategoriesModel>();
    QString selectQuery = "SELECT * FROM " + cm->GetTable();
    QString result = cm->Select(selectQuery);
    std::cout << "Select Result: " << result.toStdString() << std::endl;

    std::vector<Subcategory> subcategoryVector;
    QStringList dataVector = result.split(", ");

    for (int i = 0; i < dataVector.size(); i += 3) {
        int subcategoryId = dataVector[i].toInt();
        QString subcategoryName = dataVector[i + 1];
        int categoryId = dataVector[i + 2].toInt();

        Subcategory subcategory;
        subcategory.setId(subcategoryId);
        subcategory.setName(subcategoryName.toStdString());
        subcategory.setCategoryId(categoryId);

        subcategoryVector.push_back(subcategory);
    }
    return subcategoryVector;

}


void SubcategoriesModel::EditSubcategories(std::vector<SubcategoriesModel> items)
{
    for(SubcategoriesModel& sc : items)
    {
        sc.UpdateSubcategory();
    }
}

void SubcategoriesModel::DeleteSubcategories(std::vector<SubcategoriesModel> items)
{
    for(SubcategoriesModel& sc : items)
    {
        sc.DeleteSubcategory();
    }
}
