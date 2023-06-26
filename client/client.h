#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <memory>
#include <QDebug>
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


class Client
{
public:
    static Client& getInstance()
    {
        static Client instance; // Лише один екземпляр створюється
        return instance;
    }

    void handleServerConnection();

    bool handleLoginRequest(const std::string& email, const std::string& password);
    std::vector<Category> GetCategoties();


private:
    Client(); // Конструктор захищений, щоб заборонити створення екземплярів

    const std::string IP_ADDRESS = "127.0.0.1";
    const int PORT = 8080;

    std::unique_ptr<Poco::Net::HTTPClientSession> clientSession;
    std::unique_ptr<Poco::Net::HTTPRequest> serverRequest;
    std::unique_ptr<Poco::Net::HTTPResponse> serverResponse;

    QString retriveRequestBody() const;
    std::string retriveResponseBody() const;

    std::string sendHTTPRequest(const std::string& url);
    bool parseJSONResponse(const std::string& responseData);
};

#endif // CLIENT_H
