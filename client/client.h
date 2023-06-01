#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <memory>
#include <QDebug>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>

class Client
{
public:
    Client();

    void InitializeSession();

private:
    const std::string IP_ADDRESS = "127.0.0.1";
    const int PORT = 2323;

    std::unique_ptr<Poco::Net::HTTPClientSession> clientSession;
    std::unique_ptr<Poco::Net::HTTPRequest> requestToServer;
    std::unique_ptr<Poco::Net::HTTPResponse> serverResponse;

    void RequestToServer();
    void ServerResponse();
};

#endif // CLIENT_H
