#include "loginwindow.h"
#include "./ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)

{
    ui->setupUi(this);

    this->setWindowTitle("Sports Hub");

    QString imagePath = QCoreApplication::applicationDirPath() + "img/avatarIcon.jpg";

    imagePath.replace("build-client-Desktop_Qt_6_5_0_MinGW_64_bit-Debug", "");

    resize(600, 400);
    gridLayout = new QGridLayout;

    text_email = new QLabel(this);
    text_password = new QLabel(this);
    user_icon = new QLabel(this);

    user_icon->setPixmap(QPixmap(imagePath));
    user_icon->setFixedSize(64, 64); // Set the size of the icon

    text_email->setText("Email");
    text_email->setFont(QFont("Times", 14));
    text_email->setFixedWidth(250);

    user_name = new QLineEdit(this);
    user_name->setStyleSheet("background-color:white;border:none");
    user_name->setFixedWidth(250);
    user_name->setFixedHeight(40);

    text_password->setText("Password");
    text_password->setFont(QFont("Times", 14));
    text_password->setFixedWidth(250);

    user_password = new QLineEdit(this);
    user_password->setStyleSheet("background-color: white;border:none");
    user_password->setEchoMode(QLineEdit::EchoMode::Password);
    user_password->setFixedWidth(250);
    user_password->setFixedHeight(40);

    button = new QPushButton(this);
    button->setText("Login");
    button->setFont(QFont("Times", 14));
    button->setStyleSheet("background-color: white");
    button->setFixedWidth(200);
    button->setFixedHeight(40);

    gridLayout->addWidget(user_icon, 0, 0, 2, 2, Qt::AlignCenter);
    gridLayout->addWidget(text_email, 1, 0, 2, 2, Qt::AlignCenter);
    gridLayout->addWidget(user_name, 2, 0, 2, 2, Qt::AlignCenter);
    gridLayout->addWidget(text_password, 3, 0, 2, 2, Qt::AlignCenter);
    gridLayout->addWidget(user_password, 4, 0, 2, 2, Qt::AlignCenter);
    gridLayout->addWidget(button, 5, 0,3, 2, Qt::AlignCenter);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    connect(button, &QPushButton::clicked, this, &LoginWindow::loginPushButton_clicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QString LoginWindow::getEmail() const
{
    return user_name->text();
}

QString LoginWindow::getPassword() const
{
    return user_password->text();
}


void LoginWindow::loginPushButton_clicked()
{
    std::string email = this->user_name->text().toStdString();
    std::string password = this->user_password->text().toStdString();

    bool result = clientInstanse->handleLoginRequest(email, password);
    if(!result)
    {
        return;
    }


    adminPageWindow = std::make_unique<AdminPage>();
    clientInstanse = std::make_unique<Client>();

    connect(adminPageWindow.get(), &AdminPage::logoutDoneEvent, this, &LoginWindow::logoutPushButton_clicked);

    adminPageWindow->show();

    this->close();
}

void LoginWindow::logoutPushButton_clicked()
{
    this->user_name->setText("");
    this->user_password->setText("");
    this->show();
}