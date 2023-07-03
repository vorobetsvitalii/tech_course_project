#pragma once
#ifndef IJSONSERIALIZABLE_H
#define IJSONSERIALIZABLE_H

#include <QJsonObject>

class IJsonSerializable 
{
public:
    virtual QJsonObject GetJsonObject() = 0;
    virtual void LoadJsonObject(QJsonObject obj) = 0;
};
#endif // IJSONSERIALIZABLE_H
