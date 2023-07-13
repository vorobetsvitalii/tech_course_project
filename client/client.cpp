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

std::vector<std::unique_ptr<Entity>> Client::GetEntity(const std::string& url, const std::string& jsonName, Creator& creator)
{
    std::vector<std::unique_ptr<Entity>> entities;
    std::string key = ClientSession::getInstance()->getKey();
    std::string apiUrl = "http://" + IP_ADDRESS + ":" + std::to_string(PORT) + url + "?key=" + key;
    std::string responseData = hTTPRequestManager.sendHTTPGetRequest(apiUrl);

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString::fromStdString(responseData).toUtf8());
    if (!jsonResponse.isNull())
    {
        QJsonObject responseObject = jsonResponse.object();

        if (responseObject.contains(QString::fromStdString(jsonName)) && responseObject[QString::fromStdString(jsonName)].isArray())
        {
            QJsonArray entitiesArray = responseObject[QString::fromStdString(jsonName)].toArray();

            for (const QJsonValue& entityValue : entitiesArray)
            {
                if (entityValue.isObject())
                {
                    QJsonObject entityObject = entityValue.toObject();
                    qDebug() << entityObject;
                    std::unique_ptr<Entity> entity = creator.FactoryMethod();
                    entity->LoadJsonObject(entityObject);
                    entities.push_back(std::move(entity));
                }
            }
        }
    }
    return entities;
}

void Client::PostEntity(const std::string& url, Entity& object, Creator& creator)
{
    QJsonObject categoryObject = object.GetJsonObject();
    QJsonDocument jsonDocument(categoryObject);
    QByteArray jsonData = jsonDocument.toJson();

    std::string key = ClientSession::getInstance()->getKey();
    try {
        std::string apiUrl = "http://" + IP_ADDRESS + ":" + std::to_string(PORT) + url + "?key=" + key;
        std::string response = hTTPRequestManager.sendHTTPPostRequest(apiUrl, jsonData.toStdString());

        if (response.empty()) {
            qDebug() << "Empty response received";
        } else {
            qDebug() << "Server response: " << QString::fromStdString(response);
        }
    } catch (const std::exception& ex) {
        qDebug() << "Exception: " << ex.what();
    }
}

std::vector<Category> Client::GetCategories()
{
    CategoryCreator categoryCreator;
    std::vector<std::unique_ptr<Entity>> entities = Client::getInstance().GetEntity(Constants::categoriesApi , Constants::categoriesArrayJson, categoryCreator);

    std::vector<Category> categories;
    for (std::unique_ptr<Entity>& entity : entities)
    {
        Category* category = dynamic_cast<Category*>(entity.get());
        if (category)
        {
            categories.push_back(*category);
        }
    }

    return categories;
}

std::vector<Subcategory> Client::GetSubcategories()
{
    SubcategoryCreator subcategoryCreator;
    std::vector<std::unique_ptr<Entity>> entities = Client::getInstance().GetEntity(Constants::subcategoriesApi, Constants::subcategoriesArrayJson, subcategoryCreator);

    std::vector<Subcategory> subcategories;
    for (std::unique_ptr<Entity>& entity : entities)
    {
        Subcategory* subcategory = dynamic_cast<Subcategory*>(entity.get());
        if (subcategory)
        {
            subcategories.push_back(*subcategory);
        }
    }

    return subcategories;
}

std::vector<team> Client::GetTeams()
{
    TeamCreator teamCreator;
    std::vector<std::unique_ptr<Entity>> entities = Client::getInstance().GetEntity(Constants::teamSelect, Constants::TeamsArrayJson, teamCreator);

    std::vector<team> Teams;
    for (std::unique_ptr<Entity>& entity : entities)
    {
        team* Team = dynamic_cast<team*>(entity.get());
        if (Team)
        {
            Teams.push_back(*Team);
        }
    }

    return Teams;
}

void Client::PostCategory(const std::string& categoryName)
{
    CategoryCreator categoryCreator;
    Category* category = new Category();
    category->setName(categoryName);
    Client::getInstance().PostEntity(Constants::categoriesApi, *category, categoryCreator);
}

void Client::PostSubcategory(const std::string& subcategoryName, int categoryId)
{
    SubcategoryCreator subcategoryCreator;
    Subcategory* subcategory = new Subcategory();
    subcategory->setName(subcategoryName);
    subcategory->setCategoryId(categoryId);
    Client::getInstance().PostEntity(Constants::subcategoriesApi, *subcategory, subcategoryCreator);
}

void Client::PostTeam(team& Team)
{
    TeamCreator teamCreator;
    //team* Team= new team();
    Client::getInstance().PostEntity(Constants::teamInsert, Team , teamCreator);
}





