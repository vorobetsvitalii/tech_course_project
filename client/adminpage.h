#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include <QCoreApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QGraphicsDropShadowEffect>
#include <memory>
#include <vector>
#include <QMap>
#include <iostream>
#include <future>

#include "admininfowidget.h"
#include "addcategory.h"
#include "addsubcategory.h"
#include "execution"
#include "client.h"
#include "menubutton.h"
#include "hmenu.h"
#include "customcontextmenu.h"

namespace Ui {
class AdminPage;
}

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

private:
    Ui::AdminPage *ui;

    std::unique_ptr<QGridLayout> genericGridLayout;

    std::unique_ptr<QVBoxLayout> headerVLayout;
    std::unique_ptr<QVBoxLayout> categoriesVLayout;
    std::unique_ptr<QVBoxLayout> subcategoriesVLayout;
    std::unique_ptr<QVBoxLayout> itemsMenuVLayout;

    std::unique_ptr<QWidget> topHWidget;
    std::unique_ptr<QWidget> switchButtonWidget;
    std::unique_ptr<HMenu> menuHWidget;

    std::unique_ptr<QHBoxLayout> topHLayout;
    std::unique_ptr<QHBoxLayout> configurationHLayout;
    std::unique_ptr<QHBoxLayout> localNavigationLayout;

    std::unique_ptr<QSpacerItem> topSpacer_1;
    std::unique_ptr<QSpacerItem> topSpacer_2;
    std::unique_ptr<QSpacerItem> configSpacer_1;
    std::unique_ptr<QSpacerItem> configSpacer_2;
    std::unique_ptr<QSpacerItem> configSpacer_3;
    std::unique_ptr<QSpacerItem> configSpacer_4;
    std::unique_ptr<QSpacerItem> menuSpacer_1;
    std::unique_ptr<QSpacerItem> menuSpacer_2;
    std::unique_ptr<QSpacerItem> itemsMenuSpacer_1;
    std::unique_ptr<QSpacerItem> localNavigationSpacer_1;
    std::unique_ptr<QPushButton> homepagePushButton;
    std::unique_ptr<QPushButton> switchPushButton;
    std::unique_ptr<AdminInfoWidget> adminInfoWidget;
    std::unique_ptr<QPushButton> cancelPushButton;
    std::unique_ptr<QPushButton> saveChangesButton;
    std::unique_ptr<QPushButton> homePushButton;
    std::unique_ptr<QPushButton> pushButton_1;
    std::unique_ptr<QPushButton> pushButton_2;
    std::unique_ptr<QPushButton> pushButton_3;
    std::unique_ptr<QPushButton> pushButton_4;
    std::unique_ptr<QPushButton> pushButton_5;
    std::unique_ptr<QPushButton> pushButton_6;
    std::unique_ptr<QPushButton> pushButton_7;
    std::unique_ptr<QPushButton> pushButton_8;
    std::unique_ptr<QPushButton> pushButton_9;
    std::unique_ptr<QPushButton> addCategoryButton;
    std::unique_ptr<QPushButton> addSubcategoryButton;

    QPushButton* previousButton = nullptr;

    std::unique_ptr<QLabel> pageLabel;

    std::unique_ptr<QScrollArea> contentArea;

    std::unique_ptr<AddCategory> addCategoryWindow;
    std::unique_ptr<AddSubcategory> addSubcategoryWindow;
    std::unique_ptr<CustomContextMenu> contextMenu;

    int tempCategoryId = NULL;
    int tempSubcategoryId = NULL;

    QString tempCategory = "";
    QString tempSubcategory = "";

    std::vector<Category> categories;
    QMap<QString, int> subcategories_map;
    QMap<QString, int> subcategories_map_id;

    void initializeLayouts();
    void initializeWidgets();
    void initializeButton();
    void initializeSpacers();

    void topHorizontalLayout();
    void configurationHorizontalLayout();
    void menuHorizontalLayout();
    void itemsMenuVerticalLayout();
    void primaryContentArea();
    void appendCategories();
    void appendSubcategories();
    bool checkIfStringEmpty(const QString& temp_string);

public slots:
    void onLogoutDone();
    void on_add_category_clicked();
    void on_add_subcategory_clicked();
    void on_save_changes_clicked();
    void handleNewButtonAdded();
    void handleNewSubcategoryAdded();
    void OnMenuItemClicked(MenuButton*);
    void onCategorySelected(Category* category);
    void onCategoryClicked();
    void onSubcategoryClicked();
};

#endif // ADMINPAGE_H
