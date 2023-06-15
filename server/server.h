#ifndef MYSERVER_H
#define MYSERVER_H

#include "database.h"
#include "user.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Random.h>
#include <Poco/Base64Encoder.h>

#include <Poco/JWT/JWT.h>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/Cipher.h>
#include <Poco/Crypto/CipherKey.h>
#include <Poco/Crypto/RSAKey.h>

#include "Poco/JSON/JSON.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/PrintHandler.h"
#include "Poco/JSON/JSONException.h"

#include <Poco/URI.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTime.h>

#include <iostream>
#include <QDebug>
#include <random>
#include <algorithm>
#include <iterator>
#include <iomanip>

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};



class Server
{
public:
    Server();

    std::unique_ptr<DataBase> database;

    void start();
    void stop();

private:
    Poco::Net::HTTPServer* m_httpServer;
};

<<<<<<< HEAD
class MyRequestHandler : public Poco::Net::HTTPRequestHandler , public Server
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    bool handleLogin(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

=======





class RequestHandler : public Poco::Net::HTTPRequestHandler , public Server
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    bool CheckLogin(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

    static bool CheckToken(const std::string key);
>>>>>>> 1f012890121019ba4802d4806dfe45b04a43fc28
private:
    std::string GetLogin(Poco::Net::HTTPServerRequest& request);
    std::string GetFirstName(Poco::Net::HTTPServerRequest& request);
    std::string GetLastName(Poco::Net::HTTPServerRequest& request);
    bool DataBase_Login(const std::string ,const std::string); // Логін
    void ApiLogin(Poco::Net::HTTPServerRequest& request , Poco::Net::HTTPServerResponse& response);
    void AddTokenToBD(const std::string& token,const std::string key);


};

#endif // MYSERVER_H


std::string GenerateRandomKey();
