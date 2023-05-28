#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;

    std::unique_ptr<QTcpSocket> socket;
    QByteArray Data;

    void ConnectToHost();
    void SendToServer(QString str);

public slots:
    void slotReadyRead();
};

#endif // CLIENT_H
