#ifndef DBMODEL_H
#define DBMODEL_H
#include "../dal/idatamodel.h"

class DbModel : public IDataModel
{
public:

    virtual const QString GetTable() const = 0;
    virtual void Insert(const QString &insert_query) override;
    virtual QString Select(const QString &select_query) override;
    virtual void Update(const QString &update_query) override;
    virtual void Delete(const QString &delete_query) override;
};

#endif // DBMODEL_H
