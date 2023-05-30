#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClicked();
    void handleConnection(QString email ,QString password);

private:
    Ui::MainWindow *ui;
    QLineEdit *user_name;
    QLineEdit *user_password;
    Server serverObject;
};
#endif // MAINWINDOW_H
