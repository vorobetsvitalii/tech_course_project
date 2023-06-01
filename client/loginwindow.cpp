#include "loginwindow.h"
#include "./ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QString LoginWindow::getEmail() const
{
    return ui->emailLineEdit->text();
}

QString LoginWindow::getPassword() const
{
    return ui->passwordLineEdit->text();
}


void LoginWindow::on_loginPushButton_clicked()
{
    clientInstanse = std::make_unique<Client>();

    clientInstanse->InitializeSession();
}

