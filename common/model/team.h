#ifndef TEAM_H
#define TEAM_H
#include "../interface/IJsonSerializable.h"
#include "entity.h"
#include <QImage>
#include <QByteArray>
#include <QBuffer>
class team : public Entity
{
private:
    int TeamId;
    int SubcategoryId;
    int TeamLocation;
    QString TeamLogoBlob;
    QString TeamName;

public:
    int getTeamId();
    int getTeamLocation();
    int getSubcategoryId();
    QString getTeamLogoBlob();
    QString getTeamName();

    void setTeamId(int);
    void setTeamLocation(int);
    void setSubcategoryId(int);
    void setTeamLogoBlob(QString);
    void setTeamName(QString);

    virtual QJsonObject GetJsonObject() override;
    virtual void LoadJsonObject(QJsonObject) override;
    team();
};

#endif // TEAM_H
