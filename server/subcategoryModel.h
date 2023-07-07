#ifndef SUBCATEGORYMODEL_H
#define SUBCATEGORYMODEL_H


#include <memory>
#include "dbmodel.h"
#include "../common/model/subcategory.h"

class SubcategoriesModel : public DbModel,public Subcategory
{
public:
    SubcategoriesModel();
    SubcategoriesModel(const std::string& name);
    SubcategoriesModel(const std::string& name, int id);
    SubcategoriesModel(const std::string& name, int id, int categoryId);
    virtual const QString GetTable() const override;
    void InsertCategory();
    static std::vector<Subcategory> SelectCategory();
    void UpdateCategory();
    void DeleteCategory();
};
#endif // SUBCATEGORYMODEL_H
