#include "team.h"

int team::getTeamId()
{
    return this->TeamId;
}

int team::getTeamLocation()
{
    return this->TeamLocation;
}

int team::getSubcategoryId()
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

void team::setTeamId(int id)
{
    this->TeamId = id;
}

void team::setTeamLocation(int LocationId)
{
    this->TeamLocation = LocationId;
}

void team::setSubcategoryId(int SubcategoryId)
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
    jsonObject["TeamName"] = this->getTeamName();
    return jsonObject;
}

void team::LoadJsonObject(QJsonObject Json)
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
team::team()
{

}
