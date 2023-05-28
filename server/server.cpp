#include "server.h"



server::server(QObject *parent) : QTcpServer(parent)
{

}

bool server::handleConnection(QString email,QString password)
{

    if (model.Login(email,password )) {
        return true;

    } else {
        return false;
    }


    //додатково ,щоб повідомлення не застряло в буфері
    //socket->flush();

    //очікує на відправдку всіх данних
    //socket->waitForBytesWritten();

    //Розкоментувати , якщо потрібно перевіряти багато входів
    //socket->disconnectFromHost();
}

void server::handleDisconect()
{

}
