#include <QApplication>

#include "loginwindow.h"

#include "teamsui.h"

int main(int argc, char *argv[])
{
    Client::getInstance().GetTeams();
    QApplication a(argc, argv);


    LoginWindow loginWindowInstance;

    loginWindowInstance.show();



    return a.exec();
}
