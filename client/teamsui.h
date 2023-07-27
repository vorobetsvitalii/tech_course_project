#ifndef TEAMSUI_H
#define TEAMSUI_H

#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMessageBox>
#include <QListView>
#include <QFileDialog>
#include <QEvent>
#include <QEnterEvent>
#include <QGraphicsDropShadowEffect>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/SocketAddress.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <Poco/URI.h>
#include <iostream>
#include <future>
#include "HTTPRequestManager.h"
#include "client.h"


class TeamInterface: public QWidget
{
    Q_OBJECT

};

class TeamsUI: public QWidget
{
    Q_OBJECT
private:
    bool isImageSet = false;




protected:
    std::unique_ptr<QComboBox>LocationDrop;
    std::unique_ptr<QComboBox>CategoryDrop;
    std::unique_ptr<QComboBox>SubCategoryDrop;


    std::unique_ptr<QLineEdit>TeamInput;


    QScopedPointer<QPushButton>ApplyButton;
    std::unique_ptr<QPushButton>CancelButton;

    std::unique_ptr<QLabel>LocationLabel;
    std::unique_ptr<QLabel>CategoryLabel;
    std::unique_ptr<QLabel>SubCategoryLabel;
    std::unique_ptr<QLabel>TeamLabel;

    std::unique_ptr<QFrame>TeamImage;

    std::unique_ptr<QVBoxLayout>Layout;

    std::unique_ptr<QPushButton> CameraIcon;
    std::unique_ptr<QLabel> LogoText;

    QIcon TeamIcon;
    QString ImagePath;

    static QString comboBoxStyle;
    static QString listViewStyle;

    virtual void enterEvent(QEnterEvent* event);
    virtual void leaveEvent(QEvent* event);
    std::map<int,std::string> GetLocations();
    std::map<int,std::string> GetCategories();
    std::vector<Subcategory> GetSubCategories();
    virtual void CreateTeam() final;
    void Cancel();



public:
    std::unique_ptr<QFrame> Frame;
    static std::map<int,std::string> LocationMap;
    static std::map<int,std::string> CategoriesMap;
    std::vector<Subcategory> SubCategoriesVector;

    static std::vector<Subcategory> SubCategoriesAll;
    virtual void initializeLocationDrop();
    virtual void initializeCategoryDrop();
    virtual void initializeSubCategoryDrop();

    virtual void initializeTeamInput()final;

    virtual void initializeApplyButton();
    virtual void initializeCancelButton();

    virtual void initializeLocationLabel();
    virtual void initializeSubCategoryLabel();
    virtual void initializeTeamLabel()final;
    virtual void initializeCategoryLabel();

    virtual void initializeTeamImage()final;


    TeamsUI();
    TeamsUI(const bool);


private slots:
    void openFileExplorer();
    void onCategoryActivated(int);
};





class TeamUIFilter:public TeamsUI
{
    Q_OBJECT
private:

public:
    virtual void initializeApplyButton() override;
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;

    TeamUIFilter();
};


#endif // TEAMSUI_H