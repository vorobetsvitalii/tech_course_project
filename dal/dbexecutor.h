#ifndef DBEXECUTOR_H
#define DBEXECUTOR_H

#include <iostream>
#include <memory.h>
#include <QString>
#include <QSqlDatabase>
#include "idatamodel.h"
//#include "../server/database.h"

class DBExecutor : public IDataModel
{
public:
    DBExecutor();

    const void InitDatabase();
    const void QuitDatabase();

    virtual const std::string GetTable() const override;
    virtual void Create() override;
    virtual void Select(const std::string select_query) override;
    virtual void Update() override;
    virtual void Delete() override;

private:
    const QString DRIVER = "SQL Server";
    const QString SERVER_IP = "192.168.195.147";
    const QString DATABASE_NAME = "UJPC++2023";
    const QString UID = "UJPC++ 2023";
    const QString PASSWORD = "Tech Course UJP C++ 2023";

    QSqlDatabase databaseInstance;
};

#endif // DBEXECUTOR_H
