#ifndef DB_MODEL_H
#define DB_MODEL_H

#include<QtSql/QSql>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QSqlError>
#include<QSqlQuery>

class db_model
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

    db_model();
    db_model(QString email,QString password);

    QSqlDatabase Connect();
    bool Login();
    bool Login(QString email,QString password);

};



#endif // DB_MODEL_H