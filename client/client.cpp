#include "client.h"
#include "./ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    socket = std::make_unique<QTcpSocket>();

    connect(socket.get(), &QTcpSocket::connected, this, &Client::slotReadyRead);
    connect(socket.get(), &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);

    ConnectToHost();
}

Client::~Client()
{
    delete ui;
}

void Client::ConnectToHost()
{
    socket->connectToHost("127.0.0.1", 2323);

    if (socket->waitForConnected()) {
        qDebug() << "Connected to the host.";
    } else {
        qDebug() << "Failed to connect to the host.";
    }
}

void Client::SendToServer(QString str)
{
    Data.clear();

    QDataStream out(&Data, QDataStream::WriteOnly);

    out.setVersion(QDataStream::Qt_6_5);
    qDebug() << str;
    socket->write(Data);
}

void Client::slotReadyRead()
{
    QDataStream in(socket.get());

    in.setVersion(QDataStream::Qt_6_5);

    if(in.status() == QDataStream::Ok)
    {
        QString str;

        in >> str;
        qDebug() << str;
    }
    else
    {
        qDebug() << "Read error!\n";
    }
}
