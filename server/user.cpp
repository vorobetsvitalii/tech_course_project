#include "user.h"

User::User() {}
User::User(std::string fname, std::string lname, std::string eml,std::string lg):
    first_name(fname), last_name(lname), email(eml),logo(lg){ }

void User::set_first_name(std::string fname) { this->first_name = fname; }
void User::set_last_name(std::string lname) { this->last_name = lname; }
void User::set_email(std::string eml) { this->email = eml; }
void User::set_logo(std::string lg) { this->logo = lg; }



std::string User::get_first_name() { return first_name; }
std::string User::get_last_name() { return last_name; }
std::string User::get_email() { return email; }
std::string User::get_logo(){return logo;}

QJsonObject User::GetJsonObject()
{
    try{
    return QJsonObject {
        { QString("first_name"), QJsonValue(QString(first_name.c_str())) },
        { QString("last_name"), QJsonValue(QString(last_name.c_str())) },
        { QString("email"), QJsonValue(QString(email.c_str())) },
        { QString("logo"),QJsonValue(QString(logo.c_str()))}

        };}catch(std::exception exp){std::cout<<"\nException: "<<exp.what();}
}

void User::LoadJsonObject(QJsonObject obj)
{

    this->first_name = obj["first_name"].toString().toStdString();
    this->last_name = obj["last_name"].toString().toStdString();
    this->email = obj["email"].toString().toStdString();
    this->logo = obj["logo"].toString().toStdString();

}
