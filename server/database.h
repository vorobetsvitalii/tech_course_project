#ifndef DATABASE_H
#define DATABASE_H
#pragma once

#include<QtSql/QSql>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QSqlError>
#include<QSqlQuery>
#include<QJsonArray>
#include<QJsonObject>

class DataBase
{
private:
    const QString driver = "SQL Server";
    const QString server = "192.168.195.147";
    const QString database = "UJPC++2023";
    const QString uid = "UJPC++ 2023";
    const QString pwd = "Tech Course UJP C++ 2023";

    QString user_email;
    QString user_password;
    QString user_first_name;
    QString user_last_name;


public:


    static const QString login_check_sql;


    DataBase();
    DataBase(QString email,QString password);

    QSqlDatabase database_model = Connect();
    QSqlDatabase Connect();
    bool Login();
    bool Login(QString email,QString password);

};
#endif // DATABASE_H
