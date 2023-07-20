#include <QApplication>

#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    LoginWindow loginWindowInstance;

    loginWindowInstance.show();



    return a.exec();
}
