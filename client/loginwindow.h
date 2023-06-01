#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <memory>

#include "client.h"
#include "adminpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    QString getEmail() const;
    QString getPassword() const;

private slots:
    void on_loginPushButton_clicked();

private:
    Ui::LoginWindow *ui;

    std::unique_ptr<AdminPage> adminPageWindow;
    std::unique_ptr<Client> clientInstanse;
};
#endif // LOGINWINDOW_H
