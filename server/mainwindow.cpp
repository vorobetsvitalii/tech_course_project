#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(900, 900);

    QLabel *user_icon = new QLabel(this);
    QLabel *text_email = new QLabel(this);
    QLabel *text_password = new QLabel(this);

    text_email->setText("Email");
    text_email->setFont(QFont("Times",14));
    text_email->setGeometry(300,160,50,40);

    user_name = new QLineEdit(this);
    user_name->setGeometry(300,200,300,40);
    user_name->setStyleSheet("background-color: #BED9F4;border:none");

    text_password->setText("Password");
    text_password->setFont(QFont("Times",14));
    text_password->setGeometry(300,245,100,40);

    user_password = new QLineEdit(this);
    user_password->setGeometry(300,285,300,40);
    user_password->setStyleSheet("background-color: #BED9F4;border:none");
    user_password->setEchoMode(QLineEdit::EchoMode::Password);

    QPushButton *button = new QPushButton(this);
    button->setText("Login");
    button->setFont(QFont("Times",14));
    button->setGeometry(400,350,80,40);
    QVBoxLayout *VBox = new QVBoxLayout(this);
    VBox->addWidget(user_name);
    VBox->addWidget(user_password);
    VBox->addWidget(button);

    connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClicked()
{
    QString email = user_name->text();
    QString password = user_password->text();
    handleConnection(email, password);
}

void MainWindow::handleConnection(QString email,QString password)
{
    qDebug() << "Connecting with email: " << email << " and password: " << password;
    if (serverObject.handleConnection(email, password)) {
        qDebug() << "Successful login";
        // Виконати дії після успішного входу
    } else {
        qDebug() << "Login failed";
        // Виконати дії у разі невдалого входу
    }
}
