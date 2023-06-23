#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QToolButton>
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
    void loginPushButton_clicked();
    
public slots:
    void logoutPushButton_clicked();

private:
    Ui::LoginWindow *ui;

    QGridLayout *gridLayout;

    QLabel *text_email;
    QLabel *text_password;
    QLabel *user_icon;

    QLineEdit *user_name;
    QLineEdit *user_password;

    QPushButton *button;

    QWidget *centralWidget;

    std::unique_ptr<AdminPage> adminPageWindow;
    std::unique_ptr<Client> clientInstanse;
};
#endif // LOGINWINDOW_H
