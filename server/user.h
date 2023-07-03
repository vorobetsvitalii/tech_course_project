#pragma once

#include <iostream>
#include <string>
#include <initializer_list>

#include "../common/interface/IJsonSerializable.h"


class User : public IJsonSerializable
{
private:
    std::string first_name , last_name , email , logo ;


public:
    User();
    User(std::string fname, std::string lname, std::string eml , std::string logo);

    void set_first_name(std::string fname);
    void set_last_name(std::string lname);
    void set_email(std::string eml);
    void set_logo(std::string lg);

    std::string get_first_name();
    std::string get_last_name();
    std::string get_email();
    std::string get_logo();


    QJsonObject GetJsonObject() override;
    void LoadJsonObject(QJsonObject obj) override;

};
