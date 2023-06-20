#include "dropdownmenu.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QPalette>
#include <QMouseEvent>
#include <QDebug>

DropdownMenu::DropdownMenu(QHBoxLayout* mainLayout, QWidget* parent) : QMenu(parent)
{


    initializeNameLabel("Vitalii");
    initializeSurnameLabel("Vorobets");
    initializeEmailLabel("vitalii@gmail.com");
    initializeNameLayout();
    initializeInfoLayout();
    initializeSeparatorLine();
    initializeIcon();
    initializeLogoutButton();
    initializeButtonLayout();
    initializeButtonWidget();
    initializeMenuLayout(mainLayout);

}

void DropdownMenu::initializeNameLabel(QString name) {
    nameLabel = std::make_unique<QLabel>(name, this);
    nameLabel->setStyleSheet("color: #000000; font-family: Open Sans; font-size: 12px; font-weight:600");
}

void DropdownMenu::initializeSurnameLabel(QString surname) {
    surnameLabel = std::make_unique<QLabel>(surname, this);
    surnameLabel->setStyleSheet("color: #000000; font-family: Open Sans; font-size: 12px; font-weight:600");
}

void DropdownMenu::initializeEmailLabel(QString email) {
    emailLabel = std::make_unique<QLabel>(email, this);
    emailLabel->setStyleSheet("color: #B2B2B2; font-family: Open Sans; font-size: 12px; font-weight:400;");
}

void DropdownMenu::initializeNameLayout() {
    nameLayout = std::make_unique <QHBoxLayout>();
    nameLayout->addWidget(nameLabel.get());
    nameLayout->setAlignment(Qt::AlignLeft);
    nameLayout->setSpacing(5);
    nameLayout->addWidget(surnameLabel.get());
}

void DropdownMenu::initializeInfoLayout() {
    infoLayout = std::make_unique<QVBoxLayout>();
    infoLayout->setContentsMargins(20, 10, 15, 5);
    infoLayout->setSpacing(0);
    infoLayout->addLayout(nameLayout.get());
    infoLayout->addWidget(emailLabel.get());
}

void DropdownMenu::initializeSeparatorLine()
{
    separatorLine = std::make_unique<QFrame>(this);
    separatorLine->setFrameShape(QFrame::HLine);
    separatorLine->setFrameShadow(QFrame::Sunken);
    separatorLine->setLineWidth(0);
    separatorLine->setMidLineWidth(1);
    separatorLine->setStyleSheet("color: #B2B2B2;");

    QSizePolicy policy = separatorLine->sizePolicy();
    policy.setHorizontalStretch(1);  // Розтягнути горизонтально
    separatorLine->setSizePolicy(policy);
}

void DropdownMenu::initializeLogoutButton() {
    logoutButton = std::make_unique <QPushButton>("Logout", this);
    logoutButton->setStyleSheet("color: #000000; font-family: Open Sans; font-size: 12px; font-weight: 600; border: none;");
    logoutButton->installEventFilter(this);
    connect(logoutButton.get(), &QPushButton::clicked, this, &DropdownMenu::logout);
}

void DropdownMenu::initializeButtonLayout() {
    buttonLayout = std::make_unique <QHBoxLayout>();
    buttonLayout->addWidget(logoutButton.get());
    buttonLayout->setContentsMargins(20, 5, 15, 5);
    buttonLayout->setSpacing(70);
    buttonLayout->addWidget(armIcon.get());
    buttonLayout->addStretch();
}

void DropdownMenu::initializeButtonWidget() {
    buttonWidget = std::make_unique<QWidget>(this);
    buttonWidget->setLayout(buttonLayout.get());
    buttonWidget->setObjectName("buttonWidget");
    buttonWidget->setStyleSheet("#buttonWidget { background-color: white; }");
    buttonWidget->setFixedHeight(infoLayout->sizeHint().height());
}

void DropdownMenu::initializeIcon()
{
    armIcon = std::make_unique<QPushButton>(this);
    armIcon->setStyleSheet("QPushButton { border: none; background-color: rgba(215, 33, 48, 0); }");
    QPixmap armIconPixmap("../client/images/arm.jpg");
    armIcon->setIcon(QIcon(armIconPixmap));
    armIcon->setIconSize(QSize(25, 25));
    armIcon->hide();
}

void DropdownMenu::initializeMenuLayout(QHBoxLayout* mainLayout) {
    int menuWidth = mainLayout->sizeHint().width() - 40;
    setFixedWidth(menuWidth);
    menuLayout = std::make_unique <QVBoxLayout>(this);
    menuLayout->setContentsMargins(0,0,0,0);
    menuLayout->setSpacing(0); // Встановлюємо нульовий відступ між елементами
    menuLayout->addLayout(infoLayout.get());
    menuLayout->addWidget(separatorLine.get());
    menuLayout->addWidget(buttonWidget.get());
    setLayout(menuLayout.get());
}

void DropdownMenu::logout()
{
    qDebug() << "Logout button clicked";
}

bool DropdownMenu::eventFilter(QObject* object, QEvent* event)
{
    if (object == logoutButton.get())
    {
        if (event->type() == QEvent::Enter)
        {
            changeButtonBackgroundColor(true);
            return true;
        }
        else if (event->type() == QEvent::Leave)
        {
            changeButtonBackgroundColor(false);
            return true;
        }
    }

    return QMenu::eventFilter(object, event);
}

void DropdownMenu::changeButtonBackgroundColor(bool hover)
{
    if (hover) {
        buttonWidget->setStyleSheet("#buttonWidget { background-color: rgba(215, 33, 48, 0.11); }");
        logoutButton->setStyleSheet("color: #D72130; font-family: Open Sans; font-size: 12px; font-weight: 600; border: none; background-color: rgba(215, 33, 48, 0);");
        armIcon->show();
    } else {
        buttonWidget->setStyleSheet("#buttonWidget { background-color: white; }");
        logoutButton->setStyleSheet("color: #000000; font-family: Open Sans; font-size: 12px; font-weight: 600; border: none; background-color: white;");
        armIcon->hide();
    }
}
