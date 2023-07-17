#ifndef HTTPREQUESTMANAGER_H
#define HTTPREQUESTMANAGER_H

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <iostream>

class HTTPRequestManager
{
public:
    std::string sendHTTPPostRequest(const std::string& url, const std::string& data);
    std::string sendHTTPGetRequest(const std::string& url);
    std::string sendHTTPPutRequest(const std::string& url, const std::string& body);
    std::string sendHTTPDeleteRequest(const std::string& url);
};


#endif // HTTPREQUESTMANAGER_H
