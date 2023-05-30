#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <memory>

#include "db_model.h"

class Server : public QTcpServer
{

public:
    Server(QObject *parent = nullptr);

public slots:
    bool handleConnection(QString,QString);
    void handleDisconect();

private:
    db_model model;
    QVector<QTcpSocket*> Sockets;

    std::unique_ptr<QTcpSocket> socket;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
