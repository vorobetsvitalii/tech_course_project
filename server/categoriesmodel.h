#pragma once
#ifndef CATEGORIESMODEL_H
#define CATEGORIESMODEL_H


#include "dbmodel.h"
#include "../common/model/category.h"

class CategoriesModel : public DbModel,public Category
{
public:
    CategoriesModel(const std::string& name);
    CategoriesModel(const std::string& name, int id);
    virtual const QString GetTable() const override;
    void InsertCategory();
    void SelectCategory();
    void UpdateCategory();
    void DeleteCategory();
};
#endif // CATEGORIESMODEL_H
