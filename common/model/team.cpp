#include "team.h"

uint16_t team::getTeamId()
{
    return this->TeamId;
}

uint16_t team::getTeamLocation()
{
    return this->TeamLocation;
}

uint16_t team::getSubcategoryId()
{
    return this->SubcategoryId;
}

QString team::getTeamLogoBlob()
{
    return this->TeamLogoBlob;
}

QString team::getTeamName()
{
    return this->TeamName;
}

void team::setTeamId(uint16_t id)
{
    this->TeamId = id;
}

void team::setTeamLocation(uint16_t LocationId)
{
    this->TeamLocation = LocationId;
}

void team::setSubcategoryId(uint16_t SubcategoryId)
{
    this->SubcategoryId = SubcategoryId;
}

void team::setTeamLogoBlob(QString blob)
{
    this->TeamLogoBlob = blob;
}

void team::setTeamName(QString name)
{
    this->TeamName= name;
}

QJsonObject team::GetJsonObject()
{
    QJsonObject jsonObject;
    jsonObject["SubcategoryId"] = this->getSubcategoryId();
    jsonObject["TeamLogoBlob"] = this->getTeamLogoBlob();
    jsonObject["TeamId"] = this->getTeamId();
    jsonObject["TeamLocation"] = this->getTeamLocation();
    return jsonObject;
}

void team::LoadJsonObject(QJsonObject Json)
{
    if(Json.contains("SubcategoryId")){
        this->SubcategoryId = Json["SubcategoryId"].toInt();
    }

    if(Json.contains("TeamLogoBlob")){
        this->TeamLogoBlob = Json["TeamLocation"].toString();
    }
    if(Json.contains("TeamId")){
        this->TeamId = Json["TeamId"].toInt();
    }
    if(Json.contains("TeamLocation")){
        this->TeamLocation = Json["TeamLocation"].toInt();
    }
}

team::team()
{

}
