#include <QCoreApplication>
#include "server.h"
#include "categoriesmodel.h"



int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    CategoriesModel categoryModel("NewCategory01");
    //categoryModel.InsertCategory();
    /*categoryModel.SelectCategory();
    CategoriesModel categoryModel1("NewCategory02",23);
    categoryModel1.UpdateCategory();*/
    CategoriesModel categoryModel2("NewCategory03",26);
    //categoryModel2.UpdateCategory();
    //categoryModel.SelectCategory();
    categoryModel2.DeleteCategory();
    categoryModel.SelectCategory();
    Server server;
    server.start();

    return a.exec();
}
