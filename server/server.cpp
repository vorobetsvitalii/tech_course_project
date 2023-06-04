#include "server.h"

void MyRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    std::string method = request.getMethod();

    if (method == "GET")
    {
        std::string uri = request.getURI();

        if (uri.find("/api/login") != std::string::npos)
        {
            bool valid = handleLogin(request, response);
            if (valid)
            {
                Poco::JWT::Token token;
                token.payload().set("sub", GetLogin(request));
                token.payload().set("exp", Poco::Timestamp::fromEpochTime(std::time(nullptr) + 3600));

                std::ostringstream jwtTokenStream;
                Poco::JSON::Stringifier::stringify(token.payload(), jwtTokenStream);
                std::string jwtToken = jwtTokenStream.str();

                qDebug()<<jwtToken;

                response.setChunkedTransferEncoding(true);
                response.setContentType("application/json");

                Poco::JSON::Object result;
                result.set("status", true);
                result.set("message", "Login successful");
                result.set("first_name", GetFirstName(request));
                result.set("last_name", GetLastName(request));
                result.set("email", GetLogin(request));

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
        }
        else
        {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
            response.send();
        }
    }
}



bool MyRequestHandler::handleLogin(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    // Отримання параметрів запиту
    Poco::URI uri(request.getURI());
    std::string api = uri.getPath();
    std::string port = std::to_string(uri.getPort());

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

    // Відправка відповіді
    // Створення JSON-відповіді
    Poco::JSON::Object result;
    result.set("status", valid ? "success" : "failure");
    result.set("message", valid ? "Login successful" : "Login failed");

    // Відправка відповіді
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    //std::ostream& ostr = response.send();
    //Poco::JSON::Stringifier::stringify(result, ostr);
    return valid;
}

std::string MyRequestHandler::GetLogin(Poco::Net::HTTPServerRequest &request)
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

std::string MyRequestHandler::GetFirstName(Poco::Net::HTTPServerRequest &request)
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
    QString login_check_sql="SELECT first_name FROM Users WHERE email=:email AND password=:password";

    //Connect();
    QSqlQuery check_q;
    check_q.prepare(login_check_sql);
    check_q.bindValue(":email",QString::fromStdString(email));
    check_q.bindValue(":password",QString::fromStdString(password));

    if(check_q.exec())
    {
        if(check_q.next())
        {
            return check_q.value(0).toString().toUtf8().constData();

        }
    }
}

std::string MyRequestHandler::GetLastName(Poco::Net::HTTPServerRequest &request)
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
    QString login_check_sql="SELECT last_name FROM Users WHERE email=:email AND password=:password";

    //Connect();
    QSqlQuery check_q;
    check_q.prepare(login_check_sql);
    check_q.bindValue(":email",QString::fromStdString(email));
    check_q.bindValue(":password",QString::fromStdString(password));

    if(check_q.exec())
    {
        if(check_q.next())
        {
            return check_q.value(0).toString().toUtf8().constData();

        }
    }
}



bool MyRequestHandler::DataBase_Login(const std::string email, const std::string password)
{
    // код для перевірки БД
    qDebug() << "Calling database for login...\n";
    qDebug() << email<<":" <<QString::fromStdString(email) <<password<<":"<< QString::fromStdString(password);
    return database->Login(QString::fromStdString(email), QString::fromStdString(password));
}

Poco::Net::HTTPRequestHandler* MyRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&)
{
    return new MyRequestHandler;
}

Server::Server()
{
    Poco::Net::ServerSocket serverSocket(8080);
    Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;

    // розмір черги
    pParams->setMaxQueued(100);

    // поточність
    pParams->setMaxThreads(16);

    // створення серверу
    m_httpServer = new Poco::Net::HTTPServer(new MyRequestHandlerFactory, serverSocket, pParams);

    // ініціалізація змінної database
    database = std::make_unique<DataBase>();
}

void Server::start()
{
    m_httpServer->start();
    database->Connect();
}

void Server::stop()
{
    m_httpServer->stop();
}

std::string GenerateRandomKey()
{
    const int keyLength = 32; // Довжина секретного ключа (в байтах)

    // Використовуємо вбудований генератор випадкових чисел
    std::random_device rd;
    std::mt19937 generator(rd());

    // Створюємо випадковий ключ
    std::string secretKey;
    secretKey.resize(keyLength);
    std::generate_n(secretKey.begin(), keyLength, [&generator]() {
        std::uniform_int_distribution<int> distribution(0, 255);
        return static_cast<char>(distribution(generator));
    });

    return secretKey;
}

