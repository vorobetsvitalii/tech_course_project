#ifndef DROPDOWNMENU_H
#define DROPDOWNMENU_H

#include <QMenu>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QCursor>
#include <QPixmap>
#include <memory>

#include "client.h"

class DropdownMenu : public QMenu
{
    Q_OBJECT
public:
    explicit DropdownMenu(QHBoxLayout* mainLayout, QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* object, QEvent* event);

private:
    std::unique_ptr<QLabel> nameLabel;
    std::unique_ptr<QLabel> surnameLabel;
    std::unique_ptr<QLabel> emailLabel;
    std::unique_ptr<QVBoxLayout> menuLayout;
    std::unique_ptr<QFrame> separatorLine;
    std::unique_ptr<QHBoxLayout> nameLayout;
    std::unique_ptr<QVBoxLayout> infoLayout;
    std::unique_ptr<QHBoxLayout> buttonLayout;
    std::unique_ptr<QPushButton> logoutButton;
    std::unique_ptr<QWidget> buttonWidget;

    std::unique_ptr <QPixmap> cursorPixmap;
    std::unique_ptr <QCursor> customCursor;

    const QString nameStyle = "color: #000000; font-family: Open Sans; font-size: 12px; font-weight:600";
    const QString emailStyle = "color: #B2B2B2; font-family: Open Sans; font-size: 12px; font-weight:400;";
    const QString buttonWidgetNotHoverStyle = "#buttonWidget { background-color: white; }";
    const QString buttonWidgetHoverStyle = "#buttonWidget { background-color: rgba(215, 33, 48, 0.11); }";
    const QString logoutButtonHoverStyle = "color: #D72130; font-family: Open Sans; font-size: 12px; font-weight: 600; border: none; background-color: rgba(215, 33, 48, 0);";
    const QString logoutButtonNotHoverStyle = "color: #000000; font-family: Open Sans; font-size: 12px; font-weight: 600; border: none;";
    const QString greyColor = "color: #B2B2B2;";

    void initializeNameLabel(QString name);
    void initializeSurnameLabel(QString surname);
    void initializeEmailLabel(QString email);
    void initializeMenuLayout(QHBoxLayout* mainLayout);
    void initializeNameLayout();
    void initializeInfoLayout();
    void initializeSeparatorLine();
    void initializeButtonLayout();
    void initializeLogoutButton();
    void initializeButtonWidget();
    void initializeIcon();
    void changeButtonBackgroundColor(bool hover);
    void logout();

};

#endif // DROPDOWNMENU_H
