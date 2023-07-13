#ifndef TEAM_H
#define TEAM_H
#include "../interface/IJsonSerializable.h"

class team : public IJsonSerializable
{
private:
    uint16_t TeamId;
    uint16_t SubcategoryId;
    uint16_t TeamLocation;
    QString TeamLogoBlob;
    QString TeamName;

public:
    uint16_t getTeamId();
    uint16_t getTeamLocation();
    uint16_t getSubcategoryId();
    QString getTeamLogoBlob();
    QString getTeamName();

    void setTeamId(uint16_t);
    void setTeamLocation(uint16_t);
    void setSubcategoryId(uint16_t);
    void setTeamLogoBlob(QString);
    void setTeamName(QString);

    virtual QJsonObject GetJsonObject() override;
    virtual void LoadJsonObject(QJsonObject) override;
    team();
};

#endif // TEAM_H
