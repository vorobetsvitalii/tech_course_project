#include "client.h"
#include "loginwindow.h"

Client::Client() {}

void Client::InitializeSession()
{
    try
    {
        std::unique_ptr<Poco::Net::HTTPClientSession> clientSession = std::make_unique<Poco::Net::HTTPClientSession>(IP_ADDRESS, PORT);

        loginServerRequest();

        loginServerResponse();
    }
    catch (const Poco::Exception &ex)
    {
        qDebug() << "Poco exception: " << ex.what() << "\n";
    }
}

void Client::loginServerRequest()
{
    LoginWindow logWindow;
    QString requestBody;
    std::ostringstream requestBodyStream;

    requestBody = logWindow.getEmail() + "|" + logWindow.getPassword();

    requestToServer = std::make_unique<Poco::Net::HTTPRequest>(Poco::Net::HTTPRequest::HTTP_POST, "/", Poco::Net::HTTPMessage::HTTP_1_1);
    requestToServer->setContentType("text/plain");
    requestToServer->setContentLength(requestBody.length() + 1);

    requestBodyStream << requestBody.toStdString();

    clientSession->sendRequest(*requestToServer) << requestBodyStream.str();
}

void Client::loginServerResponse()
{
    std::unique_ptr<Poco::Net::HTTPResponse> serverResponse = std::unique_ptr<Poco::Net::HTTPResponse>();
    std::istream& responseStream = clientSession->receiveResponse(*serverResponse);

    std::string responseBody;

    Poco::StreamCopier::copyToString(responseStream, responseBody);

    qDebug() << "Response status: " << serverResponse->getStatus() << "\n";
    qDebug() << "Response body: " << responseBody << "\n";
}
