#ifndef ADMININFOWIDGET_H
#define ADMININFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFontDatabase>
#include <QPainter>
#include <memory>
#include "dropdownmenu.h"

class AdminInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminInfoWidget(QWidget *parent = nullptr);
    void showDropdownMenu();

private:
    std::unique_ptr<QLabel> photoLabel;
    std::unique_ptr<QLabel> nameLabel;
    std::unique_ptr<QLabel> surnameLabel;
    std::unique_ptr<QLabel> roleLabel;
    std::unique_ptr<QPushButton> arrowButton;
    std::unique_ptr<DropdownMenu> dropdownMenu;
    std::unique_ptr <QHBoxLayout> nameLayout;
    std::unique_ptr <QVBoxLayout> infoLayout;
    std::unique_ptr <QHBoxLayout> buttonLayout;
    std::unique_ptr <QHBoxLayout> mainLayout;
    QString pathToImages = "../img/";

    void initializePhotoLabel();
    void initializeNameLabel();
    void initializeSurnameLabel();
    void initializeRoleLabel();
    void initializeArrowButton();
    void initializeDropdownMenu();
    void initializeNameLayout();
    void initializeInfoLayout();
    void initializeButtonLayout();
    void initializeMainLayout();
};

#endif // ADMININFOWIDGET_H
