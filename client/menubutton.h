#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#pragma once;

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
    MenuButton(const QString& text, const QString& tooltip, const QIcon& icon, QWidget* parent = nullptr);
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

private:
    QIcon originalIcon;
    QPushButton* button;

    void setButtonIcon(const QIcon& icon);
    void showTooltip();
    void hideTooltip();
    QIcon convertToGrayIcon(const QIcon& icon);

protected:
    bool eventFilter(QObject* object, QEvent* event) override;



signals:
    void menuItemClicked(MenuButton* clickedButton);


};
#endif // MENUBUTTON_H

void handleMenuItemClick(MenuButton* clickedButton, QScrollArea*);


