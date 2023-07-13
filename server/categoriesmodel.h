#pragma once
#ifndef CATEGORIESMODEL_H
#define CATEGORIESMODEL_H

#include <memory>
#include "dbmodel.h"
#include "../common/model/category.h"

class CategoriesModel : public DbModel,public Category
{
public:
    CategoriesModel();
    CategoriesModel(const std::string& name);
    CategoriesModel(const std::string& name, int id);
    virtual const QString GetTable() const override;
    void InsertCategory();
    void UpdateCategory();
    void DeleteCategory();

    static std::vector<Category> SelectCategory();
    static void EditCategories(std::vector<CategoriesModel> items);
    static void DeleteCategories(std::vector<CategoriesModel> items);

};
#endif // CATEGORIESMODEL_H
