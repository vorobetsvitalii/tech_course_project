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
    void InsertSubcategory();
    void UpdateSubcategory();
    void DeleteSubcategory();

    static std::vector<Subcategory> SelectSubcategory();
    static void EditSubcategories(std::vector<SubcategoriesModel> items);
    static void DeleteSubcategories(std::vector<SubcategoriesModel> items);

};
#endif // SUBCATEGORYMODEL_H
