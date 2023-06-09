#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "../interface/IJsonSerializable.h"
#include "entity.h"


class Category: public Entity
{
private:
    int id;
    std::string name;
public:
    int getId() const;
    std::string getName() const;
    void setName(std::string name);
    void setId(int id);
    virtual QJsonObject GetJsonObject() override;
    virtual void LoadJsonObject(QJsonObject obj) override;
    friend std::ostream& operator<<(std::ostream& os, const Category& category);
};

#endif // CATEGORY_H
