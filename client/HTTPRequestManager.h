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
};


#endif // HTTPREQUESTMANAGER_H
