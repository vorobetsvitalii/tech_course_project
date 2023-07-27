#ifndef HTTPREQUESTMANAGER_H
#define HTTPREQUESTMANAGER_H

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <iostream>
#include <QDebug>

class HTTPRequestManager
{
private:
    std::string sendHTTPRequest(const std::string &url, const std::string &method, const std::string &body);
public:
    std::string sendHTTPGetRequest(const std::string& url);
    std::string sendHTTPPostRequest(const std::string& url, const std::string& data);
    std::string sendHTTPPutRequest(const std::string& url, const std::string& body);
    std::string sendHTTPDeleteRequest(const std::string& url);
};


#endif // HTTPREQUESTMANAGER_H
