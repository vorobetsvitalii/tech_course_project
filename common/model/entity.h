#ifndef ENTITY_H
#define ENTITY_H
#include "../interface/IJsonSerializable.h"

class Entity : public IJsonSerializable
{
public:
    virtual ~Entity() {}
    virtual void LoadJsonObject(QJsonObject obj) override = 0;
    virtual QJsonObject GetJsonObject() override = 0;
};

#endif // ENTITY_H
