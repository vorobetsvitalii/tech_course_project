#include "client.h"
#include "loginwindow.h"


Client::Client()
{
    handleServerConnection();
}

void Client::handleServerConnection()
{
    qDebug() << "handleServerConnection\n";
    try
    {
        clientSession = std::make_unique<Poco::Net::HTTPClientSession>(IP_ADDRESS, PORT);
        serverResponse = std::unique_ptr<Poco::Net::HTTPResponse>();

        serverRequest = std::make_unique<Poco::Net::HTTPRequest>(Poco::Net::HTTPRequest::HTTP_POST, "/", Poco::Net::HTTPMessage::HTTP_1_1);
        serverRequest->setContentType("text/plain");
        serverRequest->setContentLength(retriveRequestBody().length() + 1);

        clientSession->sendRequest(*serverRequest) << retriveRequestBody().toStdString();

        //qDebug() << "Response status: " << serverResponse->getStatus() << "\n"; Further implementation of receiving response from Server
        //qDebug() << "Response body: " << retriveResponseBody() << "\n";
    }
    catch (const Poco::Exception &ex)
    {
        qDebug() << "Poco exception: " << ex.what() << "\n";
    }
}

QString Client::retriveRequestBody() const // Need to be implemented(Server request)
{
    LoginWindow logWindow;
    QString requestBody;

    requestBody = logWindow.getEmail() + "|" + logWindow.getPassword();

    return requestBody;
}

std::string Client::retriveResponseBody() const // Need to be implemented(Server response)
{
    std::string responseBody;
    std::istream& responseStream = clientSession->receiveResponse(*serverResponse);

    Poco::StreamCopier::copyToString(responseStream, responseBody);

    return responseBody;
}

std::string Client::sendHTTPRequest(const std::string& url) {
    Poco::URI uri(url);

    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery());
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    std::istream& responseBody = session.receiveResponse(response);
    std::string responseData(std::istreambuf_iterator<char>(responseBody), {});
    return responseData;
}

bool Client::parseJSONResponse(const std::string& responseData) {
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(responseData);
    Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

    if (object->has("message")) {
        std::string message = object->getValue<std::string>("message");
        std::cout << "Message: " << message << std::endl;
    }

    if (object->has("status")) {
        std::string status = object->getValue<std::string>("status");
        std::cout << "Status: " << status << std::endl;
        std::istringstream iss(status);
        bool value;
        iss >> std::boolalpha >> value;

        if (!value) {
            return false;
        }
    }

    return true;
}

bool Client::handleLoginRequest(const std::string& email, const std::string& password) {
    qDebug() << "handleLoginRequest\n";
    std::string apiUrl = "http://127.0.0.1:8080/api/login";
    std::string query = "password=" + password + "&email=" + email;
    Poco::URI uri(apiUrl);
    uri.setQuery(query);
    std::string responseData = sendHTTPRequest(uri.toString());
    std::cout << "Response data: " << responseData << std::endl;
    bool success = parseJSONResponse(responseData);
    if (!success) {
        return false;
    }

    return true;
}

std::vector<Category> Client::GetCategoties()
{
    std::vector<Category> categories;

    std::string apiUrl = "http://127.0.0.1:8080/api/categories";
    std::string responseData = sendHTTPRequest(apiUrl);

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(responseData);
    Poco::JSON::Object::Ptr responseObject = result.extract<Poco::JSON::Object::Ptr>();

    if (responseObject->has("categories"))
    {
        Poco::JSON::Array::Ptr categoriesArray = responseObject->getArray("categories");

        for (const auto& categoryVar : *categoriesArray)
        {
            std::string categoryJson = categoryVar.toString();
            Category category = Category::fromJSON(categoryJson);
            categories.push_back(category);
        }
    }
    return categories;
}


/*    std::string responseString;
    try
    {
        // Створення HTTP клієнтської сесії
        Poco::Net::HTTPClientSession session("localhost", 8080);

        // Створення HTTP запиту GET
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/api/categories");

        // Відправка запиту
        session.sendRequest(request);

        // Отримання відповіді
        Poco::Net::HTTPResponse response;
        std::istream& responseStream = session.receiveResponse(response);
        std::ostringstream ss;
        ss << responseStream.rdbuf();
        responseString = ss.str();

        std::cout << responseString << std::endl;
        // Завершення сесії
        session.reset();
    }
    catch (const Poco::Exception& ex)
    {
        std::cerr << "Помилка: " << ex.displayText() << std::endl;
    }*/
