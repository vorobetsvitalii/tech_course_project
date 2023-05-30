#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    if(this->listen(QHostAddress::Any, 2323))
    {
        qDebug() << "Server start!";
    }
}

bool Server::handleConnection(QString email,QString password)
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

void Server::handleDisconect()
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = std::make_unique<QTcpSocket>();

    socket->setSocketDescriptor(socketDescriptor);

    connect(socket.get(), &QTcpSocket::connected, this, &Server::slotReadyRead);
    connect(socket.get(), &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);

    Sockets.push_back(socket.get());

    qDebug() << "Client connected!";
}

void Server::slotReadyRead()
{
    QDataStream in(socket.get());
    in.setVersion(QDataStream::Qt_6_5);

    if (in.status() == QDataStream::Ok)
    {
        qDebug() << "Read";
    }
    else
    {
        qDebug() << "Read error";
    }
}
