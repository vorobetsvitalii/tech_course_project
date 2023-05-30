#include <QCoreApplication>
#include "server.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    db_model connect;
    connect.Connect();

    Server serverObject;

    MainWindow w;  // Передаємо об'єкт serverObject в MainWindow
    w.setStyleSheet("background-color:#8BB9E7");
    w.show();

    return app.exec();
}
