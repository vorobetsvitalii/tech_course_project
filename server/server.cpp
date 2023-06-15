#include "server.h"

void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    try
    {
        std::string method = request.getMethod();

            //http://127.0.0.1:8080/api/login?email=user1@gmail.com&password=password1
            //http://127.0.0.1:8080/api/login?email=user2@gmail.com&password=password2

        if (method == "GET")
        {
            std::string uri = request.getURI();

            if (uri.find("/api/login") != std::string::npos)
            {
                ApiLogin(request, response);
            }
            else if(uri.find("/api/logout") != std::string::npos)
            {
                ApiLogout(request, response);
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
    }catch(std::exception exp){
         response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
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
        token.payload().set("sub", GetLogin(request));
        short int OneHour= 3600;
        token.payload().set("exp", Poco::Timestamp::fromEpochTime(std::time(nullptr) + OneHour + OneHour*2)); //час життя токену година

        std::string TokenKey = GenerateRandomKey();
        qDebug()<<TokenKey;


        Poco::JWT::Signer signer(TokenKey);
        std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
        qDebug()<<jwt;


        std::ostringstream jwtTokenStream;
        Poco::JSON::Stringifier::stringify(token.payload(), jwtTokenStream);
        std::string jwtToken = jwtTokenStream.str();

        qDebug() << jwtToken;

        //додавання токену в БД
        AddTokenToBD(jwtToken,jwt);

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
    }catch(std::exception exp){qDebug()<<exp.what();}
}

void RequestHandler::AddTokenToBD(const std::string &token , const std::string key)
{
    QSqlQuery query;

    // Розпарсування токену та отримання значення параметра "email"
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(token);
    Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
    std::string subValue = object->get("sub").toString();

    // Підготовка SQL-запиту для додавання токену до таблиці
    QString sql = "INSERT INTO Tokens (token_value, user_id,token_key) VALUES (:token, (SELECT id FROM Users WHERE email=:user_email),:key) ";
    query.prepare(sql);

    // Прив'язка значень до параметрів запиту

    query.bindValue(":token", QString::fromStdString(token));
    query.bindValue(":user_email", QString::fromStdString(subValue));
    query.bindValue(":key", QString::fromStdString(key));



    // Виконання запиту
    query.exec();
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
    QSqlQuery query;
    query.prepare("SELECT token_value FROM Tokens WHERE token_key = CAST(:key AS nvarchar(max))");
    query.bindValue(":key", QString::fromStdString(key));


    if (query.exec() && query.next())
    {
        //Значення токену в QString
        QString tokenValue = query.value(0).toString();


        std::string tokenString = tokenValue.toStdString();



        Poco::JWT::Token token;

        Poco::JSON::Parser parser;

        Poco::Dynamic::Var result = parser.parse(tokenString);

        Poco::JSON::Object::Ptr jsonObject;




        jsonObject = result.extract<Poco::JSON::Object::Ptr>();

        std::string exp = jsonObject->get("exp").toString();
        std::string sub = jsonObject->get("sub").toString();

        //токен
        token.payload().set("exp",exp);
        token.payload().set("sub",sub);



        std::istringstream TimeIss(exp);



        std::tm timeStruct = {};
        TimeIss >> std::get_time(&timeStruct, "%Y-%m-%dT%H:%M:%SZ");



        std::time_t time = std::mktime(&timeStruct);
        std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(time);



        // Форматування і виведення результату
        std::time_t timeOutput = std::chrono::system_clock::to_time_t(tp);
        std::cout << "Parsed time: " << std::put_time(std::localtime(&timeOutput), "%Y-%m-%d %H:%M:%S") << std::endl;

        // Отримання поточного часу
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        if (tp > now)
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

    QSqlQuery query;
    query.prepare("DELETE FROM Tokens WHERE token_key = CAST(:token_key AS nvarchar(max))");
    query.bindValue(":token_key", QString::fromStdString(key));
    if(query.exec())
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    else {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
    }
    response.send();
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
