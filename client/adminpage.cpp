#include "adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    ui->switchPushButton->setIcon(QPixmap("C:/Development/Projects/tech_course_project/img/switchIcon.png"));
}

AdminPage::~AdminPage()
{
    delete ui;
}
