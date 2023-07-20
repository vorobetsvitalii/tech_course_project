#ifndef TEAM_H
#define TEAM_H
#include "../interface/IJsonSerializable.h"
#include "entity.h"
#include <QImage>
#include <QByteArray>
#include <QBuffer>
class Team : public Entity
{
private:
    int TeamId;
    int SubcategoryId;
    int TeamLocation;
    QString TeamLogoBlob;
    QString TeamName;
    QString CreatingDate;

public:
    int getTeamId();
    int getTeamLocation();
    int getSubcategoryId();
    QString getTeamLogoBlob();
    QString getTeamName();
    QString getDate();

    void setTeamId(int);
    void setTeamLocation(int);
    void setSubcategoryId(int);
    void setTeamLogoBlob(QString);
    void setTeamName(QString);
    void setDate(QString);

    virtual QJsonObject GetJsonObject() override;
    virtual void LoadJsonObject(QJsonObject) override;
    Team() { TeamId=0; SubcategoryId=0; TeamLocation=0; TeamLogoBlob=""; TeamName=""; CreatingDate=""; }
};

#endif // TEAM_H
