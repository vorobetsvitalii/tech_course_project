#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <memory>

#include <QDebug>
#include <QObject>

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

#include "category.h"


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
    std::vector<Category> GetCategoties();
    void PostCategories(const std::string& categoryName);
private:
    Client();

    const std::string IP_ADDRESS = "127.0.0.1";
    const int PORT = 8080;

    std::unique_ptr<Poco::Net::HTTPClientSession> clientSession;
    std::unique_ptr<Poco::Net::HTTPRequest> serverRequest;
    std::unique_ptr<Poco::Net::HTTPResponse> serverResponse;

    QString retriveRequestBody() const;
    std::string retriveResponseBody() const;

    std::string sendHTTPRequest(const std::string& url);
    std::string sendHTTPPostRequest(const std::string& url, const std::string& body);
    bool parseJSONResponse(const std::string& responseData);

signals:
    void logoutDoneEvent();

};

#endif // CLIENT_H
