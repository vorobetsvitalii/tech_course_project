#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#pragma once

#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QToolTip>
#include <QWidget>
#include <QScrollArea>
#include <map>

class MenuButton : public QPushButton
{
    Q_OBJECT

public:
    MenuButton(const QString& name, const QString& tooltip, const QIcon& icon, QWidget* parent = nullptr);
    void SetAdvertising(MenuButton* clickedButton ,QScrollArea* Content);
    void SetBanners(MenuButton* clickedButton ,QScrollArea* Content);
    void SetNewsPartners(MenuButton* clickedButton ,QScrollArea* Content);
    void SetSocialNetworks(MenuButton* clickedButton ,QScrollArea* Content);
    void SetSurveys(MenuButton* clickedButton ,QScrollArea* Content);
    void SetFooter(MenuButton* clickedButton ,QScrollArea* Content);
    void SetTeams(MenuButton* clickedButton ,QScrollArea* Content);
    void SetUsers(MenuButton* clickedButton ,QScrollArea* Content);
    void SetLanguages(MenuButton* clickedButton ,QScrollArea* Content);
    void SetIA(MenuButton* clickedButton ,QScrollArea* Content);

    QIcon GetIcon();
    bool clicked;

    QString GetItemName();

    void setButtonIcon(const QIcon& icon);
    QIcon convertToGrayIcon(const QIcon& icon);
private:

    std::unique_ptr<QWidget> advertisingContent=initializeAdvertisingContent();
    std::unique_ptr<QWidget> bannersContent=initializeBannersContent();
    std::unique_ptr<QWidget> newsPartnersContent=initializeNewsPartnersContent();
    std::unique_ptr<QWidget> socialNetworksContent=initializeSocialNetworksContent();
    std::unique_ptr<QWidget> surveysContent=initializeSurveysContent();
    std::unique_ptr<QWidget> footerContent=initializeFooterContent();
    std::unique_ptr<QWidget> teamsContent=initializeTeamsContent();
    std::unique_ptr<QWidget> usersContent=initializeUsersContent();
    std::unique_ptr<QWidget> languagesContent=initializeLanguagesContent();
    std::unique_ptr<QWidget> iaContent=initializeIAContent();


    QPushButton* button;
    QIcon originalIcon;
    QString buttonName;

    void showTooltip();
    void hideTooltip();


    std::unique_ptr<QWidget> initializeAdvertisingContent();
    std::unique_ptr<QWidget> initializeBannersContent();
    std::unique_ptr<QWidget> initializeNewsPartnersContent();
    std::unique_ptr<QWidget> initializeSocialNetworksContent();
    std::unique_ptr<QWidget> initializeSurveysContent();
    std::unique_ptr<QWidget> initializeFooterContent();
    std::unique_ptr<QWidget> initializeTeamsContent();
    std::unique_ptr<QWidget> initializeUsersContent();
    std::unique_ptr<QWidget> initializeLanguagesContent();
    std::unique_ptr<QWidget> initializeIAContent();


protected:
    bool eventFilter(QObject* object, QEvent* event) override;



signals:
    void menuItemClicked(MenuButton* clickedButton);


};
#endif // MENUBUTTON_H

void handleMenuItemClick(MenuButton* clickedButton, QScrollArea*);


