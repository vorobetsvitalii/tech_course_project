#include "client.h"
#include "loginwindow.h"
#include "clientsession.h"


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
    //LoginWindow logWindow;
    QString requestBody;

    requestBody = ""; //logWindow.getEmail() + "|" + logWindow.getPassword();

    return requestBody;
}

std::string Client::retriveResponseBody() const // Need to be implemented(Server response)
{
    std::string responseBody;
    std::istream& responseStream = clientSession->receiveResponse(*serverResponse);

    Poco::StreamCopier::copyToString(responseStream, responseBody);

    return responseBody;
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

    if(object->has("key")) {
        std::string key = object->getValue<std::string>("key");
        ClientSession::getInstance()->setKey(key);
    }

    if(object->has("first_name")) {
        std::string firstName = object->getValue<std::string>("first_name");
        ClientSession::getInstance()->setFirstName(firstName);
    }

    if(object->has("last_name")) {
        std::string lastName = object->getValue<std::string>("last_name");
        ClientSession::getInstance()->setLastName(lastName);
    }

    if(object->has("email")) {
        std::string email = object->getValue<std::string>("email");
        ClientSession::getInstance()->setEmail(email);
    }


    return true;
}

bool Client::handleLoginRequest(const std::string& email, const std::string& password) {
    qDebug() << "handleLoginRequest\n";
    std::string apiUrl = "http://127.0.0.1:8080/api/login";
    std::string query = "password=" + password + "&email=" + email;
    Poco::URI uri(apiUrl);
    uri.setQuery(query);
    std::string responseData = hTTPRequestManager.sendHTTPGetRequest(uri.toString());
    std::cout << "Response data: " << responseData << std::endl;
    bool success = parseJSONResponse(responseData);
    if (!success) {
        return false;
    }

    return true;
}

bool Client::handleLogoutRequest() {
    std::string key = ClientSession::getInstance()->getKey();
    std::string url = "http://" + IP_ADDRESS + ":" + std::to_string(PORT) + "/api/logout?key="+key;

    Poco::Net::HTTPClientSession session(IP_ADDRESS, PORT);
    Poco::Net::HTTPRequest request = Poco::Net::HTTPRequest(Poco::Net::HTTPRequest::HTTP_GET, url);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    if(response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK){
        ClientSession::deleteInstance();
        emit this->logoutDoneEvent();
        return true;
    }
    return false;
}

std::vector<Category> Client::GetCategoties()
{
    std::vector<Category> categories;
    std::string key = ClientSession::getInstance()->getKey();
    std::string apiUrl = "http://" + IP_ADDRESS + ":" + std::to_string(PORT) + "/api/categories?key="+key;
    std::string responseData = hTTPRequestManager.sendHTTPGetRequest(apiUrl);

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
    for(int i = 0; i<categories.size(); i++)
    {
        std::cout << categories[i] << std::endl;
    }
    return categories;
}

void Client::PostCategories(const std::string& categoryName)
{
    try {
        // Створення JSON об'єкту з назвою категорії
        Poco::JSON::Object categoryObject;
        std::string key = ClientSession::getInstance()->getKey();
        categoryObject.set("CategoryName", categoryName);
        categoryObject.set("key", key);

        // Серіалізація JSON об'єкту в рядок
        std::stringstream jsonStream;
        categoryObject.stringify(jsonStream);
        std::string json = jsonStream.str();

        // Відправка POST-запиту
        std::string apiUrl = "http://" + IP_ADDRESS + ":" + std::to_string(PORT) + "/api/categories";
        std::string response = hTTPRequestManager.sendHTTPPostRequest(apiUrl, json);

        // Обробка відповіді сервера
        if (response.empty()) {
            qDebug() << "Empty response received";
        } else {
            qDebug() << "Server response: " << QString::fromStdString(response);
        }
    } catch (const std::exception& ex) {
        qDebug() << "Exception: " << ex.what();
    }
}


