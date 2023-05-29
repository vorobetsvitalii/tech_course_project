#include "User.h"

User::User() {}
User::User(string fname, string lname, string eml, string pswd):
    first_name(fname), last_name(lname), email(eml), password(pswd) { }

void User::set_first_name(string fname) { this->first_name = fname; }
void User::set_last_name(string lname) { this->last_name = lname; }
void User::set_email(string eml) { this->email = eml; }
void User::set_password(string pswd) { this->password = pswd; }

string User::get_first_name() { return first_name; }
string User::get_last_name() { return last_name; }
string User::get_email() { return email; }
string User::get_password() { return password; }

QJsonObject User::GetJsonObject()
{
    return QJsonObject {
        { QString("first_name"), QJsonValue(QString(first_name.c_str())) },
        { QString("last_name"), QJsonValue(QString(last_name.c_str())) },
        { QString("email"), QJsonValue(QString(email.c_str())) },
        { QString("password"), QJsonValue(QString(password.c_str())) }
    };
}

void User::LoadJsonObject(QJsonObject obj)
{
    if(obj["email"].isUndefined() || obj["password"].isUndefined()) {
        return;
    }
    this->first_name = obj["first_name"].toString().toStdString();
    this->last_name = obj["last_name"].toString().toStdString();
    this->email = obj["email"].toString().toStdString();
    this->password = obj["password"].toString().toStdString();
}
