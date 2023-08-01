#include "admininfowidget.h"
#include "clientsession.h"

AdminInfoWidget::AdminInfoWidget(QWidget *parent) : QWidget(parent) {
    QString fontRoute = "../client/fonts/OpenSans-Regular.ttf";
    QFontDatabase::addApplicationFont(fontRoute);
    initializePhotoLabel();
    initializeNameLabel();
    initializeSurnameLabel();
    initializeRoleLabel();
    initializeArrowButton();
    initializeNameLayout();
    initializeInfoLayout();
    initializeButtonLayout();
    initializeMainLayout();
    initializeDropdownMenu();
}

void AdminInfoWidget::initializePhotoLabel() {
    photoLabel = std::make_unique<QLabel>(this);
    photoLabel->setFixedSize(40, 40);
    QString imagePath = pathToImages + "avatarIcon.jpg";
    QImage photoImage(imagePath);

    QPixmap photoPixmap = QPixmap::fromImage(photoImage).scaled(QSize(40, 40), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QBitmap mask(photoPixmap.size());
    mask.fill(Qt::color0);

    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::color1);
    painter.setBrush(Qt::color1);
    painter.drawEllipse(mask.rect());

    photoPixmap.setMask(mask);

    photoLabel->setPixmap(photoPixmap);
    photoLabel->setScaledContents(true);
}

void AdminInfoWidget::initializeNameLabel() {
    nameLabel = std::make_unique<QLabel>(QString::fromStdString(ClientSession::getInstance()->getFirstName()), this);
    nameLabel->setStyleSheet(nameStyle);
}

void AdminInfoWidget::initializeSurnameLabel() {
    surnameLabel = std::make_unique<QLabel>(QString::fromStdString(ClientSession::getInstance()->getLastName()), this);
    surnameLabel->setStyleSheet(nameStyle);
}

void AdminInfoWidget::initializeRoleLabel() {
    roleLabel = std::make_unique<QLabel>("Administrator", this);
    roleLabel->setStyleSheet(roleStyle);
}

void AdminInfoWidget::initializeNameLayout() {
    nameLayout = std::make_unique<QHBoxLayout>();
    nameLayout->addWidget(nameLabel.get());
    nameLayout->setSpacing(5);
    nameLayout->addWidget(surnameLabel.get());
}

void AdminInfoWidget::initializeInfoLayout() {
    infoLayout = std::make_unique <QVBoxLayout>();
    infoLayout->setContentsMargins(0, 2, 0, 0);

    infoLayout->addLayout(nameLayout.get());
    infoLayout->addWidget(roleLabel.get());
    infoLayout->setSpacing(3);
    infoLayout->setAlignment(Qt::AlignTop);
}

void AdminInfoWidget::initializeArrowButton() {
    arrowButton = std::make_unique<QPushButton>(this);
    arrowButton->setStyleSheet(arrowStyle);
    QPixmap arrowPixmap(pathToImages + "chevron_down.png");
    arrowButton->setIcon(QIcon(arrowPixmap));
    arrowButton->setIconSize(QSize(8, 8));
}

void AdminInfoWidget::initializeButtonLayout() {
    buttonLayout = std::make_unique <QHBoxLayout>();
    buttonLayout->addWidget(arrowButton.get());
    buttonLayout->setContentsMargins(0, 0, 0, 7);
}

void AdminInfoWidget::initializeMainLayout() {
    mainLayout = std::make_unique <QHBoxLayout>(this);
    mainLayout->addWidget(photoLabel.get());
    mainLayout->addLayout(infoLayout.get());
    mainLayout->addLayout(buttonLayout.get());
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setContentsMargins(0, 0, 20, 0);
    mainLayout->setSpacing(10);
    setLayout(mainLayout.get());

    QSize nameSize = nameLabel->sizeHint();
    QSize surnameSize = surnameLabel->sizeHint();
    int widgetWidth = qMax(nameSize.width(), surnameSize.width()) + 60;
    int widgetHeight = qMax(nameSize.height() + surnameSize.height() + 10, 70);
    resize(widgetWidth, widgetHeight);
}

void AdminInfoWidget::initializeDropdownMenu() {
    dropdownMenu = std::make_unique<DropdownMenu>(mainLayout.get(), this);
    connect(arrowButton.get(), &QPushButton::clicked, this, &AdminInfoWidget::showDropdownMenu);
}

void AdminInfoWidget::showDropdownMenu()
{
    if (dropdownMenu->isVisible()) {
        dropdownMenu->hide();
    } else {
        QPoint pos = mapToGlobal(arrowButton->pos());
        pos.setY(pos.y() + arrowButton->height());
        dropdownMenu->show();

        int menuX = pos.x() - dropdownMenu->width() + 20;
        dropdownMenu->move(menuX, pos.y());
    }
}

