#include "HTTPRequestManager.h"

Poco::Net::HTTPClientSession HTTPRequestManager::createHTTPClientSession(const std::string& url)
{
    Poco::URI uri(url);
    return Poco::Net::HTTPClientSession(uri.getHost(), uri.getPort());
}

std::string HTTPRequestManager::receiveHTTPResponse(Poco::Net::HTTPClientSession& session)
{
    Poco::Net::HTTPResponse response;
    std::istream& responseBody = session.receiveResponse(response);
    return std::string(std::istreambuf_iterator<char>(responseBody), {});
}

std::string HTTPRequestManager::sendHTTPRequestWithBody(const std::string& url, const std::string& method, const std::string& body)
{
    try {
        Poco::Net::HTTPClientSession session = createHTTPClientSession(url);
        Poco::Net::HTTPRequest request(method, Poco::URI(url).getPathAndQuery());
        request.setContentType("application/json");
        request.setContentLength(body.length());
        std::ostream& requestBody = session.sendRequest(request);
        requestBody << body;
        return receiveHTTPResponse(session);
    } catch (const Poco::Exception& ex) {
        std::cout << "Poco exception: " << ex.displayText() << std::endl;
        return "";
    }
}

std::string HTTPRequestManager::sendHTTPGetRequest(const std::string& url)
{
    Poco::Net::HTTPClientSession session = createHTTPClientSession(url);
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, Poco::URI(url).getPathAndQuery());
    session.sendRequest(request);
    return receiveHTTPResponse(session);
}

std::string HTTPRequestManager::sendHTTPPostRequest(const std::string& url, const std::string& body)
{
    return sendHTTPRequestWithBody(url, Poco::Net::HTTPRequest::HTTP_POST, body);
}

std::string HTTPRequestManager::sendHTTPPutRequest(const std::string& url, const std::string& body)
{
    return sendHTTPRequestWithBody(url, Poco::Net::HTTPRequest::HTTP_PUT , body);
}

std::string HTTPRequestManager::sendHTTPDeleteRequest(const std::string& url)
{
    Poco::Net::HTTPClientSession session = createHTTPClientSession(url);
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_DELETE, Poco::URI(url).getPathAndQuery());
    session.sendRequest(request);
    return receiveHTTPResponse(session);
}
