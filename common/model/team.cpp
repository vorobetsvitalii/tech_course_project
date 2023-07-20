#include "team.h"

int Team::getTeamId()
{
    return this->TeamId;
}

int Team::getTeamLocation()
{
    return this->TeamLocation;
}

int Team::getSubcategoryId()
{
    return this->SubcategoryId;
}

QString Team::getTeamLogoBlob()
{
    return this->TeamLogoBlob;
}

QString Team::getTeamName()
{
    return this->TeamName;
}

QString Team::getDate()
{
    return this->CreatingDate;
}

void Team::setTeamId(int id)
{
    this->TeamId = id;
}

void Team::setTeamLocation(int LocationId)
{
    this->TeamLocation = LocationId;
}

void Team::setSubcategoryId(int SubcategoryId)
{
    this->SubcategoryId = SubcategoryId;
}

void Team::setTeamLogoBlob(QString blob)
{
    this->TeamLogoBlob = blob;
}

void Team::setTeamName(QString name)
{
    this->TeamName= name;
}

void Team::setDate(QString Date)
{
    this->CreatingDate=Date;
}

QJsonObject Team::GetJsonObject()
{
    QJsonObject jsonObject;
    jsonObject["SubcategoryId"] = this->getSubcategoryId();
    jsonObject["TeamLogoBlob"] = this->getTeamLogoBlob();
    jsonObject["TeamId"] = this->getTeamId();
    jsonObject["TeamLocation"] = this->getTeamLocation();
    jsonObject["TeamName"] = this->getTeamName();
    jsonObject["CreatingDate"] = this->getDate();
    return jsonObject;
}

void Team::LoadJsonObject(QJsonObject Json)
{
    if(Json.contains("SubcategoryId")){
        this->SubcategoryId = Json["SubcategoryId"].toInt();
    }


    if(Json.contains("TeamId")){
        this->TeamId = Json["TeamId"].toInt();
    }
    if(Json.contains("TeamLocation")){
        this->TeamLocation = Json["TeamLocation"].toInt();
    }
    if(Json.contains("TeamName")){
        this->TeamName = Json["TeamName"].toString();
    }

    if(Json.contains("CreatingDate")){
        this->CreatingDate = Json["CreatingDate"].toString();
    }

    if(Json.contains("TeamLogoBlob")){
        this->TeamLogoBlob = Json["TeamLogoBlob"].toString();
        QImage image(this->getTeamLogoBlob());
        if (image.isNull()) {
            // Обробка помилки завантаження зображення
            return;
        }

        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);

        image.save(&buffer , "png");

        // Отримуємо масив байтів з буфера
        imageData = buffer.buffer();
        this->setTeamLogoBlob(QString::fromLatin1(imageData.toBase64()));


        //перевірка чи після конвертації не відбулось втрати
        //QByteArray byteArray = QByteArray::fromBase64(this->getTeamLogoBlob().toLatin1());
        //bool isIdentical = (byteArray == imageData);

    }
}

