#include <iostream>
#include <QDebug>

#include "querybuilder.h"

int main()
{
    QList<QString> columnsName;

    columnsName.append("Name");
    columnsName.append("Age");

    QList<QPair<QString, QString>> whereCond;

    whereCond.append(QPair<QString, QString>("Name", "Sasha"));
    whereCond.append(QPair<QString, QString>("Age", "18"));

    std::cout << QueryBuilder::DeleteQueryBuild("Consumer", whereCond).toStdString();

    return 0;
}
