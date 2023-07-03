#ifndef IDATAMODEL_H
#define IDATAMODEL_H

#include <iostream>
#include <QString>
#include <future>

class IDataModel
{
public:
    virtual ~IDataModel() {}

    virtual const QString GetTable() const = 0;
    virtual void Insert(const QString &insert_query) = 0;
    virtual QString Select(const QString &select_query) = 0;
    virtual void Update(const QString &update_query) = 0;
    virtual void Delete(const QString &delete_query) = 0;
};

#endif // IDATAMODEL_H
