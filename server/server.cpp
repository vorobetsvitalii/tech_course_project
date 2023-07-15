#include "server.h"

void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    try
    {
        std::string method = request.getMethod();
        std::string uri = request.getURI();

        //http://127.0.0.1:8080/api/login?email=user1@gmail.com&password=password1
        //http://127.0.0.1:8080/api/login?email=user2@gmail.com&password=password2

        if (method == "GET")
        {
            if (uri.find(Constants::loginApi) != std::string::npos)
            {
                ApiLogin(request, response);
            }
            else if(uri.find(Constants::logoutApi) != std::string::npos)
            {
                ApiLogout(request, response);
            }
            else if(uri.find(Constants::categoriesApi) != std::string::npos)
            {
                ApiGetCategories(request, response);
            }
            else if(uri.find(Constants::subcategoriesApi) != std::string::npos)
            {
                GetSubcategories(request, response);
            }
            else if(uri.find(Constants::locationsGet) != std::string::npos)
            {
                GetLocations(request, response);
            }
            else if(uri.find(Constants::teamSelect) != std::string::npos)
            {
                GetTeams(request, response);

            }
            else if(uri.find("/test")!= std::string::npos)
            {
                //повністю для тесту запитів
                Poco::URI uri(request.getURI());
                Poco::URI::QueryParameters parameters = uri.getQueryParameters();
                std::string key;
                for (auto a:parameters) {
                    key=a.second;
                }
                CheckToken(key);
            }
            else
            {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
                response.send();
            }
        }
        else if (method == "POST")
        {
            qDebug() << "POST\n";
            if (uri.find(Constants::categoriesApi) != std::string::npos)
            {
                qDebug() << "categories\n";
                ApiPostCategories(request, response);
            }
            if (uri.find(Constants::subcategoriesApi) != std::string::npos)
            {
                qDebug() << "subcategories\n";
                PostSubcategories(request, response);
            }
            if(uri.find(Constants::teamInsert)!=std::string::npos)
            {
                qDebug()<< "team";
                PostTeam(request, response);
            }
            else
            {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
                response.send();
            }
        }
    }catch(std::exception* exp){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
        qDebug() << exp->what();
        response.send();
    }
}



bool RequestHandler::CheckLogin(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    // Отримання параметрів запиту
    Poco::URI uri(request.getURI());

    Poco::URI::QueryParameters parameters = uri.getQueryParameters();

    for (const auto& param : parameters)
    {
        std::string key = param.first;
        std::string value = param.second;

        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }


    std::string login;
    std::string password;

    for (const auto& param : parameters)
    {
        if (param.first == "email")
        {
            login = param.second;
        }
        else if (param.first == "password")
        {
            password = param.second;
        }
    }

    // Виклик методу БД для перевірки даних
    bool valid = DataBase_Login(login, password);

    return valid;
}

std::string RequestHandler::GetLogin(Poco::Net::HTTPServerRequest &request)
{
    Poco::URI uri(request.getURI());
    Poco::URI::QueryParameters parameters = uri.getQueryParameters();


    for (const auto& param : parameters)
    {
        if (param.first == "email")
        {
            return param.second;
        }
    }
    return NULL;
}

std::string RequestHandler::GetFirstName(Poco::Net::HTTPServerRequest &request)
{


    Poco::URI uri(request.getURI());
    Poco::URI::QueryParameters parameters = uri.getQueryParameters();

    std::string email;
    std::string password;
    for (const auto& param : parameters)
    {
        if (param.first == "email")
        {
            email = param.second;
        }
        else if(param.first=="password")
        {
            password=param.second;
        }
    }
    //переробити
    QString login_check_sql = DataBase::login_check_sql;

    //DataBase::database_model.open() ;
    QSqlQuery check_q;
    check_q.prepare(login_check_sql);
    check_q.bindValue(":email",QString::fromStdString(email));
    check_q.bindValue(":password",QString::fromStdString(password));

    if(check_q.exec())
    {
        if(check_q.next())
        {
            qDebug()<<check_q.value("first_name").toString().toUtf8().constData();
            return check_q.value("first_name").toString().toUtf8().constData();

        }
    }
    return NULL;
}

std::string RequestHandler::GetLastName(Poco::Net::HTTPServerRequest &request)
{
    Poco::URI uri(request.getURI());
    Poco::URI::QueryParameters parameters = uri.getQueryParameters();

    std::string email;
    std::string password;
    for (const auto& param : parameters)
    {
        if (param.first == "email")
        {
            email = param.second;
        }
        else if(param.first=="password")
        {
            password=param.second;
        }
    }
    //переробити
    QString login_check_sql = DataBase::login_check_sql;

    //Connect();
    //DataBase::database_model.open() ;
    QSqlQuery check_q;
    check_q.prepare(login_check_sql);
    check_q.bindValue(":email",QString::fromStdString(email));
    check_q.bindValue(":password",QString::fromStdString(password));

    if(check_q.exec())
    {
        if(check_q.next())
        {
            qDebug()<<check_q.value("last_name").toString().toUtf8().constData();
            return check_q.value("last_name").toString().toUtf8().constData();

        }
    }
    return NULL;
}

bool RequestHandler::DataBase_Login(const std::string email, const std::string password)
{
    // код для перевірки БД
    qDebug() << "Calling database for login...\n";
    qDebug() << email<<":" <<QString::fromStdString(email) <<password<<":"<< QString::fromStdString(password);
    return database->Login(QString::fromStdString(email), QString::fromStdString(password));
}

void RequestHandler::ApiLogin(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    try{
        bool valid = CheckLogin(request, response);
        if (valid)
        {
            Poco::JWT::Token token;
            Poco::DateTime currentDateTime;
            Poco::DateTime expirationDateTime = currentDateTime + Poco::Timespan(3600, 0);
            Poco::Timestamp expirationTimestamp = expirationDateTime.timestamp();

            token.setExpiration(expirationTimestamp);
            auto exp1 = token.getExpiration();

            token.payload().set("sub", GetLogin(request));
            short int OneHour = 3600;
            token.payload().set("exp", expirationTimestamp);

            std::string TokenKey = GenerateRandomKey();
            qDebug() << TokenKey;

            Poco::JWT::Signer signer(TokenKey);
            std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
            qDebug() << jwt;


            std::ostringstream jwtTokenStream;
            Poco::JSON::Stringifier::stringify(token.payload(), jwtTokenStream);
            std::string jwtToken = jwtTokenStream.str();

            qDebug() << jwtToken;

            //додавання токену в map
            storage::AddToken(token,jwt);

            response.setChunkedTransferEncoding(true);
            response.setContentType("application/json");

            Poco::JSON::Object result;
            result.set("status", true);
            result.set("message", "Login successful");
            result.set("first_name", GetFirstName(request));
            result.set("last_name", GetLastName(request));
            result.set("email", GetLogin(request));
            result.set("key",jwt);


            // Додавання токену до відповіді
            result.set("token", jwtToken);

            std::ostream& ostr = response.send();
            Poco::JSON::Stringifier::stringify(result, ostr);
        }
        else
        {
            // Обробка невдалого входу
            Poco::JSON::Object result;
            response.setChunkedTransferEncoding(true);
            response.setContentType("application/json");

            result.set("status", false);
            result.set("message", "Login failed");
            std::ostream& ostr = response.send();
            Poco::JSON::Stringifier::stringify(result, ostr);
        }
    }catch(const std::exception& exp){qDebug()<<exp.what();}
}


bool RequestHandler::CheckToken(const std::string key)
{
    /*
    RequestHandler::CheckToken("eyJhbGciOiJIUzI1NiJ9.eyJleHAiOiIyMDIzLTA2LTE1VDExOjI1OjI3WiIsInN1YiI6InVzZXI2MEBnbWFpbC5jb20ifQ.iuoDG-Uu-8TGnmlik4pPSnkdKC63htrQgn2vi0N_SXQ");
    RequestHandler::CheckToken("eyJhbGciOiJIUzI1NiJ9.eyJleHAiOiIyMDIzLTA2LTE1VDA5OjE4OjM5WiIsInN1YiI6InVzZXI1NUBnbWFpbC5jb20ifQ.ely3c9G48gW1iV3COJFqyG-HIe4ROG141pitegnHw8w");
    RequestHandler::CheckToken("eyJhbGciOiJIUzI1NiJ9.eyJleHAiOiIyMDIzLTA2LTE1VDAwOjI2OjQzWiIsInN1YiI6InVzZXIyQGdtYWlsLmNvbSJ9.S6PKY5AIwSiHNdsVcSltocaMIuoX3cS061aEk-E80yw");
    RequestHandler::CheckToken("eyJhbGciOiJIUzI1NiJ9.eyJleHAiOiIyMDIzLTA2LTE0VDIxOjE5OjU3WiIsInN1YiI6InVzZXIyQGdtYWlsLmNvbSJ9.aH2mntmfgEffylIvdqAK6IHaZ30P5DIvjk2sKJVYXeY");
    RequestHandler::CheckToken("eyJhbGciOiJIUzI1NiJ9.eyJleHAiOiIyMDIzLTA2LTE0VDIxOjE5OjQzWiIsInN1YiI6InVzZXIyQGdtYWlsLmNvbSJ9.tzw2B-gvtHntK6-ApZVL564fPcaq5NMPolJQwa1ylOY");
    */

    try {
        Poco::JWT::Token token = storage::GetTokenFromStorage(key);

        auto& payload = token.payload();
        Poco::Timestamp expirationTimestamp;
        if (payload.has("exp")) {
            Poco::Dynamic::Var expVar = payload.get("exp");

            expirationTimestamp = expVar.convert<Poco::Timestamp>();
            std::cout << "Expiration: " << expirationTimestamp.epochTime() << std::endl;
        }



        // Отримання поточного часу

        Poco::Timestamp currentTimestamp(std::time(nullptr));
        if (expirationTimestamp > currentTimestamp)
        {
            qDebug()<<"Токен валідний";
            return true;
        }
        else
        {
            qDebug()<<"Токен невалідний";
            return false;
        }


        //auto a = signer.verify(token.toString());
        ///if (signer.tryVerify(tokenString, token)) {}


    }

    catch (const Poco::Exception& exp)
    {
        // Обробка помилки при розпакуванні токену
        std::cout<<"Token error";
        return false;
    }
    return false;
}

void RequestHandler::ApiLogout(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response){
    Poco::URI::QueryParameters parameters = Poco::URI(request.getURI()).getQueryParameters();
    std::string key = parameters[0].second;
    try {
        storage::DeleteTokenByKey(key);
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    }
    catch(std::exception& ex){
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    response.send();
}

void RequestHandler::ApiGetCategories(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse& response)
{
    try {
        Poco::URI::QueryParameters parameters = Poco::URI(request.getURI()).getQueryParameters();
        std::string key = parameters[0].second;
        if(CheckToken(key))
        {
            std::vector<Category> categoriesVector = CategoriesModel::SelectCategory();

            QJsonArray categoriesArray;
            for (Category& category : categoriesVector) {
                QJsonObject categoryObject = category.GetJsonObject();
                categoriesArray.append(categoryObject);
            }

            QJsonObject responseObject;
            responseObject["categories"] = categoriesArray;
            qDebug() << responseObject;
            QJsonDocument responseDocument(responseObject);
            QByteArray responseData = responseDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("application/json");
            response.setContentLength(responseData.length());
            response.sendBuffer(responseData.data(), responseData.length());
        }
        else
        {
            QJsonObject errorObject;
            errorObject["error"] = "Unauthorized";
            errorObject["message"] = "Invalid token";

            QJsonDocument errorDocument(errorObject);
            QByteArray errorData = errorDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.setContentLength(errorData.length());
            response.sendBuffer(errorData.data(), errorData.length());
        }
    }
    catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("text/plain");
        response.sendBuffer(e.what(), std::strlen(e.what()));

    }
}


void RequestHandler::ApiPostCategories(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    try {
        std::istream& requestBody = request.stream();
        std::string body;
        Poco::StreamCopier::copyToString(requestBody, body);

        Poco::URI::QueryParameters parameters = Poco::URI(request.getURI()).getQueryParameters();
        std::string key = parameters[0].second;

        QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray::fromStdString(body));
        if (jsonDocument.isNull()) {
            throw std::runtime_error("Invalid JSON data");
        }

        QJsonObject categoryObject = jsonDocument.object();
        if (CheckToken(key)) {
            qDebug() << categoryObject << "\n";

            std::unique_ptr<CategoriesModel> model = std::make_unique<CategoriesModel>();
            model->LoadJsonObject(categoryObject);
            model->InsertCategory();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("text/plain");
            response.sendBuffer("Category added successfully", 26);
        }
        else {
            QJsonObject errorObject;
            errorObject["error"] = "Unauthorized";
            errorObject["message"] = "Invalid token";

            QJsonDocument errorDocument(errorObject);
            QByteArray errorData = errorDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.setContentLength(errorData.length());
            response.sendBuffer(errorData.data(), errorData.length());
        }
    }
    catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("text/plain");
        response.sendBuffer(e.what(), std::strlen(e.what()));
    }
}

void RequestHandler::GetSubcategories(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse& response)
{
    try {
        Poco::URI::QueryParameters parameters = Poco::URI(request.getURI()).getQueryParameters();
        std::string key = parameters[0].second;
        if(CheckToken(key))
        {
            std::vector<Subcategory> subcategoriesVector = SubcategoriesModel::SelectSubcategory();

            QJsonArray subcategoriesArray;
            for (Subcategory& subcategory : subcategoriesVector) {
                QJsonObject subcategoryObject = subcategory.GetJsonObject();
                subcategoriesArray.append(subcategoryObject);
            }

            QJsonObject responseObject;
            responseObject["subcategories"] = subcategoriesArray;
            qDebug() << responseObject;
            QJsonDocument responseDocument(responseObject);
            QByteArray responseData = responseDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("application/json");
            response.setContentLength(responseData.length());
            response.sendBuffer(responseData.data(), responseData.length());
        }
        else
        {
            QJsonObject errorObject;
            errorObject["error"] = "Unauthorized";
            errorObject["message"] = "Invalid token";

            QJsonDocument errorDocument(errorObject);
            QByteArray errorData = errorDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.setContentLength(errorData.length());
            response.sendBuffer(errorData.data(), errorData.length());
        }
    }
    catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("text/plain");
        response.sendBuffer(e.what(), std::strlen(e.what()));

    }
}

void RequestHandler::PostSubcategories(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    try {
        std::istream& requestBody = request.stream();
        std::string body;
        Poco::StreamCopier::copyToString(requestBody, body);

        Poco::URI::QueryParameters parameters = Poco::URI(request.getURI()).getQueryParameters();
        std::string key = parameters[0].second;

        QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray::fromStdString(body));
        if (jsonDocument.isNull()) {
            throw std::runtime_error("Invalid JSON data");
        }

        QJsonObject subcategoryObject = jsonDocument.object();
        if (CheckToken(key)) {
            qDebug() << subcategoryObject << "\n";

            std::unique_ptr<SubcategoriesModel> model = std::make_unique<SubcategoriesModel>();
            model->LoadJsonObject(subcategoryObject);
            qDebug() << model->getName();
            model->InsertSubcategory();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("text/plain");
            response.sendBuffer("Category added successfully", 26);
        }
        else {
            QJsonObject errorObject;
            errorObject["error"] = "Unauthorized";
            errorObject["message"] = "Invalid token";

            QJsonDocument errorDocument(errorObject);
            QByteArray errorData = errorDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.setContentLength(errorData.length());
            response.sendBuffer(errorData.data(), errorData.length());
        }
    }
    catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("text/plain");
        response.sendBuffer(e.what(), std::strlen(e.what()));
    }
}

void RequestHandler::GetLocations(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    TeamModel Team;
    QJsonObject locationJson = Team.LocationJson(Team.SelectLocations());

    try
    {
        // Встановити заголовок відповіді на JSON
        response.setContentType("application/json");

        // Конвертувати об'єкт JSON в рядок JSON
        QByteArray jsonData = QJsonDocument(locationJson).toJson();

        // Встановити рядок JSON як тіло відповіді
        response.sendBuffer(jsonData.data(), jsonData.size());
    }
    catch (const Poco::JSON::JSONException& e)
    {
        // Обробити помилку розбору JSON
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.send() << "Error parsing JSON: " << e.message();
    }
}

void RequestHandler::PostTeam(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    try {
        std::istream& requestBody = request.stream();
        std::string body;
        Poco::StreamCopier::copyToString(requestBody, body);

        Poco::URI::QueryParameters parameters = Poco::URI(request.getURI()).getQueryParameters();
        std::string key = parameters[0].second;

        QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray::fromStdString(body));
        if (jsonDocument.isNull()) {
            throw std::runtime_error("Invalid JSON data");
        }

        QJsonObject teamObject = jsonDocument.object();
        if (CheckToken(key)) {
            qDebug() << teamObject << "\n";

            std::unique_ptr<TeamModel> model = std::make_unique<TeamModel>();
            model->LoadJsonObject(teamObject);
            model->InsertTeam();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("text/plain");
            response.sendBuffer("Team added successfully", 26);
        }
        else {
            QJsonObject errorObject;
            errorObject["error"] = "Unauthorized";
            errorObject["message"] = "Invalid token";

            QJsonDocument errorDocument(errorObject);
            QByteArray errorData = errorDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.setContentLength(errorData.length());
            response.sendBuffer(errorData.data(), errorData.length());
        }
    }
    catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("text/plain");
        response.sendBuffer(e.what(), std::strlen(e.what()));
    }
}

void RequestHandler::GetTeams(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    try {
        Poco::URI::QueryParameters parameters = Poco::URI(request.getURI()).getQueryParameters();
        std::string key = parameters[0].second;
        if(CheckToken(key))
        {
            std::vector<team> TeamsVector = TeamModel::SelectTeam();

            QJsonArray TeamsArray;
            for (team& Team : TeamsVector) {
                QJsonObject teamObject = Team.GetJsonObject();
                TeamsArray.append(teamObject);
            }

            QJsonObject responseObject;
            responseObject["Teams"] = TeamsArray;
            qDebug() << responseObject;
            QJsonDocument responseDocument(responseObject);
            QByteArray responseData = responseDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("application/json");
            response.setContentLength(responseData.length());
            response.sendBuffer(responseData.data(), responseData.length());
        }
        else
        {
            QJsonObject errorObject;
            errorObject["error"] = "Unauthorized";
            errorObject["message"] = "Invalid token";

            QJsonDocument errorDocument(errorObject);
            QByteArray errorData = errorDocument.toJson();

            response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            response.setContentType("application/json");
            response.setContentLength(errorData.length());
            response.sendBuffer(errorData.data(), errorData.length());
        }
    }
    catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType("text/plain");
        response.sendBuffer(e.what(), std::strlen(e.what()));

    }
}


Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&)
{
    return new RequestHandler;
}

Server::Server()
{
    Poco::Net::SocketAddress address("127.0.0.1", 8080);
    Poco::Net::ServerSocket serverSocket(address);
    Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;

    // розмір черги
    pParams->setMaxQueued(100);

    // поточність
    pParams->setMaxThreads(16);

    // створення серверу
    m_httpServer = new Poco::Net::HTTPServer(new RequestHandlerFactory, serverSocket, pParams);

    // ініціалізація змінної database
    database = std::make_unique<DataBase>();
}

void Server::start()
{
    m_httpServer->start();
    database->Connect();
    //database->ClearTokens();
}

void Server::stop()
{
    m_httpServer->stop();
}

std::string GenerateRandomKey()
{
    const int keyLength = 32;

    // Використовуємо вбудований генератор випадкових чисел
    std::random_device rd;
    std::mt19937 generator(rd());

    // Створюємо випадковий ключ
    std::uniform_int_distribution<int> distribution(0, 255);
    std::stringstream ss;
    for (int i = 0; i < keyLength; i++) {
        int randomByte = distribution(generator);
        ss << std::hex << std::setw(2) << std::setfill('0') << randomByte;
    }

    std::string readableKey = ss.str();

    return readableKey;
}
