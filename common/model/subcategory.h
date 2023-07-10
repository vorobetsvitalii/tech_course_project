#ifndef SUBCATEGORY_H
#define SUBCATEGORY_H

#include <string>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "../interface/IJsonSerializable.h"
#include "entity.h"


class Subcategory: public Entity
{
private:
    int id;
    int categoryId;
    std::string name;
public:
    int getId() const;
    int getCategoryId() const;
    std::string getName() const;
    void setName(std::string name);
    void setId(int id);
    void setCategoryId(int categoryId);
    virtual QJsonObject GetJsonObject() override;
    virtual void LoadJsonObject(QJsonObject obj) override;
    friend std::ostream& operator<<(std::ostream& os, const Subcategory& subcategory);
};

#endif // SUBCATEGORY_H
