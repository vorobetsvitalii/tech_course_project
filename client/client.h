#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <memory>

#include <QDebug>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>

#include <Poco/URI.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <Poco/Crypto/Cipher.h>
#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/CipherKey.h>
#include <Poco/Exception.h>
#include <stdexcept>
#include <cstring>

#include "../common/model/category.h"
#include "../common/model/entity.h"
#include "../common/model/subcategory.h"
#include "../common/model/team.h"
#include "../common/model/categoryCreator.h"
#include "../common/model/subcategoryCreator.h"
#include "../common/model/teamCreator.h"
#include "../common/constants.h"
#include "HTTPRequestManager.h"


class Client: public QObject
{
    Q_OBJECT

public:
    static Client& getInstance()
    {
        static Client instance;
        return instance;
    }

    void handleServerConnection();

    bool handleLoginRequest(const std::string& email, const std::string& password);
    bool handleLogoutRequest();
    std::vector<std::unique_ptr<Entity>> GetEntity(const std::string& url, const std::string& jsonName, Creator& creator);



    void PostEntity(const std::string& url, Entity& object);

    void EditEntity(const std::string& url, Entity& object);
    void DeleteEntity(const std::string& url, const std::string& objectId);
    std::vector<Category> GetCategories();
    std::vector<Subcategory> GetSubcategories();
    std::vector<Team> GetTeams();
    void PostCategory(const std::string& categoryName);
    void PostSubcategory(const std::string& subcategoryName, int categoryId);

    void PostTeam(Team& team);
    void EditCategory(Category& category);
    void DeleteCategory(Category& category);
    void EditSubcategory(Subcategory& subcategory);
    void EditTeam(Team& team);
    void DeleteSubcategory(Subcategory& subcategory);
    void DeleteTeam(Team& team);



private:
    Client();

    static std::string IP_ADDRESS;
    static int PORT;

    HTTPRequestManager hTTPRequestManager;

    std::unique_ptr<Poco::Net::HTTPClientSession> clientSession;
    std::unique_ptr<Poco::Net::HTTPRequest> serverRequest;
    std::unique_ptr<Poco::Net::HTTPResponse> serverResponse;

    static std::vector<Subcategory> subcategories;

    QString retriveRequestBody() const;
    std::string retriveResponseBody() const;
    bool parseJSONResponse(const std::string& responseData);

signals:
    void logoutDoneEvent();

};

#endif // CLIENT_H
