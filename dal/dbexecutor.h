#ifndef DBEXECUTOR_H
#define DBEXECUTOR_H

#include <iostream>
#include <memory.h>
#include <QDebug>
#include <QString>
#include <QtSql>
#include "idatamodel.h"

class DBExecutor : public IDataModel
{
public:
    DBExecutor();

    const void InitDatabase();
    const void QuitDatabase();

    virtual const QString GetTable() const override;
    virtual void Insert(const QString &insert_query) override;
    virtual QString Select(const QString &select_query) override;
    virtual void Update(const QString &update_query) override;
    virtual void Delete(const QString &delete_query) override;

private:
    const QString DRIVER = "SQL Server";
    const QString SERVER_IP = "192.168.195.147";
    const QString DATABASE_NAME = "UJPC++2023";
    const QString UID = "UJPC++ 2023";
    const QString PASSWORD = "Tech Course UJP C++ 2023";

    QSqlDatabase mDatabase;
};

#endif // DBEXECUTOR_H
