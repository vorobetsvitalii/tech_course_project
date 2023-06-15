#pragma once

#include <QJsonObject>

class IJsonSerializable
{
public:
    virtual QJsonObject GetJsonObject() = 0;
    virtual void LoadJsonObject(QJsonObject obj) = 0;
};
