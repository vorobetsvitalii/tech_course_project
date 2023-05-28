#ifndef SERVER_H
#define SERVER_H



#include <QTcpServer>
#include <QTcpSocket>
#include "db_model.h"

class server : public QTcpServer
{

public:
    server(QObject *parent = nullptr);

public slots:
    bool handleConnection(QString,QString);
    void handleDisconect();

private:
    db_model model;
};

#endif // SERVER_H
