#include "adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    this->setWindowTitle("Sports Hub");

    QString imagePath = QCoreApplication::applicationDirPath() + "img/switchIcon.png";

    imagePath.replace("build-client-Desktop_Qt_6_5_0_MinGW_64_bit-Debug", "");

    ui->switchPushButton->setIcon(QPixmap(imagePath));
}

AdminPage::~AdminPage()
{
    delete ui;
}
