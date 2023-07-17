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

class TeamsUI: public QWidget
{
    Q_OBJECT
private:
    bool isImageSet = false;

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


protected:

    static QString comboBoxStyle;
    static QString listViewStyle;

    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    std::map<int,std::string> GetLocations();
    std::map<int,std::string> GetCategories();
    std::vector<Subcategory> GetSubCategories();
    void CreateTeam();
    void Cancel();



public:
    static std::map<int,std::string> LocationMap;
    static std::map<int,std::string> CategoriesMap;
    std::vector<Subcategory> SubCategoriesVector;

    static std::vector<Subcategory> SubCategoriesAll;
    void initializeLocationDrop();
    void initializeCategoryDrop();
    void initializeSubCategoryDrop();

    void initializeTeamInput();

    void initializeApplyButton();
    void initializeCancelButton();

    void initializeLocationLabel();
    void initializeSubCategoryLabel();
    void initializeTeamLabel();
    void initializeCategoryLabel();

    void initializeTeamImage();

    void ApplyButtonCheck();

    TeamsUI();




private slots:
    void openFileExplorer();
    void onCategoryActivated(int);
};


#endif // TEAMSUI_H
