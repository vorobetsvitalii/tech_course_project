#pragma once

#include <string>
#include <initializer_list>

#include "interface/IJsonSerializable.h"

using namespace std;

class User : public IJsonSerializable  
{
private:
    string first_name, last_name, email, password;

public:
    User();
    User(string fname, string lname, string eml, string pswd);

    void set_first_name(string fname);
    void set_last_name(string lname);
    void set_email(string eml);
    void set_password(string pswd);

    string get_first_name();
    string get_last_name();
    string get_email();
    string get_password();

    QJsonObject GetJsonObject();
    void LoadJsonObject(QJsonObject obj);

};
