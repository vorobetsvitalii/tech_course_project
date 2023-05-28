#include "db_model.h"

db_model::db_model()
{

}

db_model::db_model(QString email, QString password )
{
    this->user_email = email;
    this->user_password = password;
}

QSqlDatabase db_model::Connect()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={%1};SERVER=%2;DATABASE=%3;UID=%4;PWD=%5;")
                           .arg(driver, server, database, uid, pwd));


    if(db.open()){
        qDebug()<<"Connecting to db....\nSuccessfully\n";
    }else{ qDebug()<<"Connecting to db....\nFailed\n"<<db.lastError();}
    return db;
}

bool db_model::Login()
{
    //QSqlDatabase db = this->Connect();


    QString login_check_sql="SELECT * FROM Users WHERE email=:email AND password=:password";

    QSqlQuery check_q;
    check_q.prepare(login_check_sql);
    check_q.bindValue(":email", this->user_email);
    check_q.bindValue(":password", this->user_password);

    if(check_q.exec()){

        if(check_q.next()){


                    return true;
        }
    }


    return false;
}

bool db_model::Login(QString email, QString password)
{

    QString login_check_sql="SELECT * FROM Users WHERE email=:email AND password=:password";

    QSqlQuery check_q;
    check_q.prepare(login_check_sql);
    check_q.bindValue(":email", email);
    check_q.bindValue(":password", password);

    if(check_q.exec()){

        if(check_q.next()){

                    return true;
        }
    }

    return false;
}
