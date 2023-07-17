#include "HTTPRequestManager.h"

std::string HTTPRequestManager::sendHTTPGetRequest(const std::string &url)
{
    Poco::URI uri(url);

    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery());
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    std::istream& responseBody = session.receiveResponse(response);
    std::string responseData(std::istreambuf_iterator<char>(responseBody), {});
    return responseData;
}

std::string HTTPRequestManager::sendHTTPPostRequest(const std::string &url, const std::string &body)
{
    try {
        Poco::URI uri(url);
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, uri.getPathAndQuery());
        request.setContentType("application/json");
        request.setContentLength(body.length());

        std::ostream& requestBody = session.sendRequest(request);
        requestBody << body;

        Poco::Net::HTTPResponse response;
        std::istream& responseBody = session.receiveResponse(response);
        std::string responseData(std::istreambuf_iterator<char>(responseBody), {});

        return responseData;
    } catch (const Poco::Exception& ex) {
        std::cout << "Poco exception: " << ex.displayText() << std::endl;
        return ""; // Повертаємо пустий рядок у випадку помилки
    }
}

std::string HTTPRequestManager::sendHTTPPutRequest(const std::string& url, const std::string& body)
{
    try {
        Poco::URI uri(url);
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, uri.getPathAndQuery());
        request.setContentType("application/json");
        request.setContentLength(body.length());

        std::ostream& requestBody = session.sendRequest(request);
        requestBody << body;

        Poco::Net::HTTPResponse response;
        std::istream& responseBody = session.receiveResponse(response);
        std::string responseData(std::istreambuf_iterator<char>(responseBody), {});

        return responseData;
    } catch (const Poco::Exception& ex) {
        std::cout << "Poco exception: " << ex.displayText() << std::endl;
        return ""; // Повертаємо пустий рядок у випадку помилки
    }
}

std::string HTTPRequestManager::sendHTTPDeleteRequest(const std::string& url)
{
    try {
        Poco::URI uri(url);
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_DELETE, uri.getPathAndQuery());

        Poco::Net::HTTPResponse response;
        session.sendRequest(request);
        std::istream& responseBody = session.receiveResponse(response);
        std::string responseData(std::istreambuf_iterator<char>(responseBody), {});

        return responseData;
    } catch (const Poco::Exception& ex) {
        std::cout << "Poco exception: " << ex.displayText() << std::endl;
        return ""; // Повертаємо пустий рядок у випадку помилки
    }
}

