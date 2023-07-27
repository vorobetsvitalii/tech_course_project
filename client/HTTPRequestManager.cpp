#include "HTTPRequestManager.h"

std::string HTTPRequestManager::sendHTTPRequest(const std::string &url, const std::string &method, const std::string &body)
{
    try {
        Poco::URI uri(url);
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

        Poco::Net::HTTPRequest request(method, uri.getPathAndQuery());
        if (!body.empty()) {
            request.setContentType("application/json");
            request.setContentLength(body.length());
        }

        if (method == "POST" || method == "PUT") {
            std::ostream& requestBody = session.sendRequest(request);
            requestBody << body;
        } else {
            session.sendRequest(request);
        }

        Poco::Net::HTTPResponse response;
        std::istream& responseBody = session.receiveResponse(response);
        std::string responseData(std::istreambuf_iterator<char>(responseBody), {});

        return responseData;
    } catch (const Poco::Exception& ex) {
        std::cout << "Poco exception: " << ex.displayText() << std::endl;
        return ""; // Return an empty string in case of an error
    }
}


std::string HTTPRequestManager::sendHTTPGetRequest(const std::string &url)
{
    return sendHTTPRequest(url, "GET", "");
}

std::string HTTPRequestManager::sendHTTPPostRequest(const std::string &url, const std::string &body)
{
    return sendHTTPRequest(url, "POST", body);
}

std::string HTTPRequestManager::sendHTTPPutRequest(const std::string &url, const std::string &body)
{
    return sendHTTPRequest(url, "PUT", body);
}

std::string HTTPRequestManager::sendHTTPDeleteRequest(const std::string &url)
{
    return sendHTTPRequest(url, "DELETE", "");
}
