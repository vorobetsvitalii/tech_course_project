#include "dbexecutor.h"

DBExecutor::DBExecutor() {}

const void DBExecutor::InitDatabase()
{
    mDatabase = QSqlDatabase::addDatabase("QODBC");

    QString connectionString = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;")
                                   .arg(SERVER_IP)
                                   .arg(DATABASE_NAME);

    mDatabase.setDatabaseName(connectionString);
    mDatabase.setUserName(UID);
    mDatabase.setPassword(PASSWORD);

    if (mDatabase.open())
    {
        qDebug() << "Connected to database!\n";
    }
    else
    {
        qDebug() << "Failed to connect to database:" << mDatabase.lastError().text();
    }
}

const void DBExecutor::QuitDatabase()
{
    if(mDatabase.isOpen())
    {
        mDatabase.close();
        qDebug() << "Disconnected from database!\n";
    }
}

const QString DBExecutor::GetTable() const
{
    return "";
}

void DBExecutor::Insert(const QString &insert_query)
{
    InitDatabase();

    QSqlQuery query;

    query.prepare(insert_query);

    if (query.exec()) {
        qDebug() << "Insert query executed successfully!";
    }
    else
    {
        qDebug() << "Failed to execute insert query:" << query.lastError().text();
    }

    QuitDatabase();
}

QString DBExecutor::Select(const QString &select_query)
{
    InitDatabase();

    QSqlQuery query;
    query.prepare(select_query);

    if (query.exec()) {
        QStringList dataList; // List to store the retrieved data

        while (query.next()) {
            for (int i = 0; i < query.record().count(); i++) {
                QString fieldData = query.value(i).toString();
                dataList.append(fieldData);
            }
        }

        QuitDatabase();

        if (!dataList.isEmpty()) {
            QString data = dataList.join(", ");
            return data;
        } else {
            qDebug() << "No records found!";
        }
    } else {
        qDebug() << "The query wasn't executed!";
    }

    QuitDatabase();

    return "Query Error";
}

void DBExecutor::Update(const QString &update_query)
{
    InitDatabase();

    QSqlQuery query;

    query.prepare(update_query);

    if (query.exec())
    {
        qDebug() << "Update query executed successfully!";
    }
    else
    {
        qDebug() << "Failed to execute update query:" << query.lastError().text();
    }

    QuitDatabase();
}

void DBExecutor::Delete(const QString &delete_query)
{
    InitDatabase();

    QSqlQuery query;

    query.prepare(delete_query);

    if (query.exec())
    {
        qDebug() << "Delete query executed successfully!";
    }
    else
    {
        qDebug() << "Failed to execute delete query:" << query.lastError().text();
    }

    QuitDatabase();
}
