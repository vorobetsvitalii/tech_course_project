#include "adminpage.h"
#include "ui_adminpage.h"
#include <functional>

AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    this->resize(820, 480);
    this->setWindowTitle("Sports Hub");
    this->setStyleSheet("QWidget {background-color: rgb(255, 255, 255); }");

    addCategoryWindow = std::make_unique<AddCategory>();
    addSubcategoryWindow  = std::make_unique<AddSubcategory>();
    addTeamWindow = std::make_unique<AddTeams>();

    categoryCustomMenu = std::make_unique<CategoryCustomMenu>();
    contextMenu = std::make_unique<CustomContextMenu>();
    teamContextMenu = std::make_unique<TeamContextMenu>();

    initializeLayouts(); // Tools initialization
    initializeButton();
    initializeSpacers();

    initializeWidgets(); // Widgets creations

    topHorizontalLayout(); // Layouts creation
    configurationHorizontalLayout();
    menuHorizontalLayout();
    itemsMenuVerticalLayout();

    primaryContentArea(); // Content area creation

    localNavigationLayout->addLayout(itemsMenuVLayout.get()); // Generic grid layout forming
    localNavigationLayout->addSpacerItem(localNavigationSpacer_1.get());
    localNavigationLayout->addWidget(contentArea.get());

    appendCategories();
    appendSubcategories();
    appendTeams();

    genericGridLayout->addWidget(topHWidget.get(), 0, 0); // Generic grid layout forming
    genericGridLayout->addLayout(configurationHLayout.get(), 1, 0);
    genericGridLayout->addWidget(menuHWidget.get(), 2, 0);
    genericGridLayout->addLayout(localNavigationLayout.get(), 3, 0);

    genericGridLayout->setContentsMargins(0, 0, 0, 0);

    connect(&Client::getInstance(), &Client::logoutDoneEvent, this, &AdminPage::onLogoutDone);
    connect(addCategoryButton.get(), &QPushButton::clicked, this, &AdminPage::on_add_category_clicked);
    connect(addSubcategoryButton.get(), &QPushButton::clicked, this, &AdminPage::on_add_subcategory_clicked);
    connect(addTeamButton.get(), &QPushButton::clicked, this, &AdminPage::on_add_team_clicked);
    connect(addCategoryWindow.get(), &AddCategory::newButtonAdded, this, &AdminPage::handleNewButtonAdded);
    connect(addSubcategoryWindow.get(), &AddSubcategory::newButtonAdded, this, &AdminPage::handleNewSubcategoryAdded);
    connect(addTeamWindow.get(), &AddTeams::newButtonAdded, this, &AdminPage::handleNewTeamAdded);
    connect(saveChangesButton.get(), &QPushButton::clicked, this, &AdminPage::on_save_changes_clicked);
}

AdminPage::~AdminPage()
{
    delete ui;
}

void AdminPage::initializeLayouts()
{
    genericGridLayout = std::make_unique<QGridLayout>(this);

    headerVLayout = std::make_unique<QVBoxLayout>();
    topHLayout = std::make_unique<QHBoxLayout>();
    configurationHLayout = std::make_unique<QHBoxLayout>();

    localNavigationLayout = std::make_unique<QHBoxLayout>();
    itemsMenuVLayout = std::make_unique<QVBoxLayout>();
    categoriesVLayout = std::make_unique<QVBoxLayout>();
    subcategoriesVLayout = std::make_unique<QVBoxLayout>();
    teamsVLayout = std::make_unique<QVBoxLayout>();
}

void AdminPage::initializeWidgets()
{
    topHWidget = std::make_unique<QWidget>();
    switchButtonWidget = std::make_unique<QWidget>();
    menuHWidget = std::make_unique<HMenu>();
    connect(menuHWidget.get(), &HMenu::categorySelected, this, &AdminPage::onCategorySelected);
    adminInfoWidget = std::make_unique<AdminInfoWidget>();
}

void AdminPage::initializeButton()
{
    // Top layout
    homepagePushButton = std::make_unique<QPushButton>();
    switchPushButton = std::make_unique<QPushButton>();
    // Configuration layout
    cancelPushButton = std::make_unique<QPushButton>();
    saveChangesButton = std::make_unique<QPushButton>();
    // Menu layout
    homePushButton = std::make_unique<QPushButton>();
    // Items menu layout
    pushButton_1 = std::make_unique<QPushButton>();
    pushButton_2 = std::make_unique<QPushButton>();
    pushButton_3 = std::make_unique<QPushButton>();
    pushButton_4 = std::make_unique<QPushButton>();
    pushButton_5 = std::make_unique<QPushButton>();
    pushButton_6 = std::make_unique<QPushButton>();
    pushButton_7 = std::make_unique<QPushButton>();
    pushButton_8 = std::make_unique<QPushButton>();
    pushButton_9 = std::make_unique<QPushButton>();

    addCategoryButton = std::make_unique<QPushButton>();
    addSubcategoryButton = std::make_unique<QPushButton>();
    addTeamButton = std::make_unique<QPushButton>();
}


void AdminPage::initializeSpacers()
{
    // Top layout
    topSpacer_1 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    topSpacer_2 = std::make_unique<QSpacerItem>(15, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Configuration layout
    configSpacer_1 = std::make_unique<QSpacerItem>(60, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    configSpacer_2 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    configSpacer_3 = std::make_unique<QSpacerItem>(9, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    configSpacer_4 = std::make_unique<QSpacerItem>(40, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Menu layout
    //menuSpacer_1 = std::make_unique<QSpacerItem>(52, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    //menuSpacer_2 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    // Items menu layout
    itemsMenuSpacer_1 = std::make_unique<QSpacerItem>(20, 30, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Primary content area
    localNavigationSpacer_1 = std::make_unique<QSpacerItem>(10, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void AdminPage::topHorizontalLayout()
{
    QFontDatabase::addApplicationFont("../client/fonts/OpenSans-SemiBold.ttf");
    QFontDatabase::addApplicationFont("../client/fonts/OpenSans-Bold.ttf");

    QFont homepagePushButtonFont("Open Sans", 14);
    //QString projectPath = QCoreApplication::applicationDirPath();

    homepagePushButton->setText("Sports Hub");
    homepagePushButton->setFixedSize(170, 60);
    homepagePushButton->setFont(homepagePushButtonFont);
    homepagePushButton->setStyleSheet("background-color: #D72130; \
                                       color: rgb(255, 255, 255); \
                                       border:none;\
                                       font-weight: 600;");

    switchPushButton->setStyleSheet("border: none; \
                                     margin-left: 10px;");

    switchPushButton->setIcon(QIcon("../img/switcher.svg"));
    switchPushButton->setIconSize(QSize(35, 40));

    topHLayout->addWidget(homepagePushButton.get());
    topHLayout->addSpacerItem(topSpacer_1.get());
    topHLayout->addWidget(switchPushButton.get());
    topHLayout->addSpacerItem(topSpacer_2.get());
    topHLayout->addWidget(adminInfoWidget.get());
    topHWidget->setLayout(topHLayout.get());

    topHWidget->setObjectName("topHWidget");
    topHWidget->setStyleSheet("#topHWidget {"
                              "border-bottom: 1px solid rgb(211, 211, 211);"
                              "}");

    topHLayout->setContentsMargins(0, 0, 0, 0);
    topHLayout->setSpacing(0);

}

void AdminPage::configurationHorizontalLayout()
{
    cancelPushButton->setText("\"Cancel\"");
    cancelPushButton->resize(56, 20);
    cancelPushButton->setStyleSheet("QPushButton { \
                                     background-color: rgb(255, 255, 255); \
                                     color: rgb(255, 0, 0); border:none}");

    saveChangesButton->setText("Save");
    saveChangesButton->setFixedSize(110, 30);
    saveChangesButton->setStyleSheet("QPushButton { \
                                      background-color: rgb(208, 0, 0); \
                                      color: rgb(255, 255, 255); border:none}");

    QFont homeLabelFont("Open Sans", 16, QFont::Bold);

    pageLabel = std::make_unique<QLabel>();

    pageLabel->setText("Home");
    pageLabel->setFont(homeLabelFont);

    configurationHLayout->addSpacerItem(configSpacer_1.get());
    configurationHLayout->addWidget(pageLabel.get());
    configurationHLayout->addSpacerItem(configSpacer_2.get());
    //configurationHLayout->addWidget(cancelPushButton.get());
    configurationHLayout->addSpacerItem(configSpacer_3.get());
    configurationHLayout->addWidget(saveChangesButton.get());
    configurationHLayout->addSpacerItem(configSpacer_4.get());
}

void AdminPage::menuHorizontalLayout()
{
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(menuHWidget.get());


shadowEffect->setBlurRadius(8);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    shadowEffect->setOffset(0, 4);

    menuHWidget->setGraphicsEffect(shadowEffect);
    menuHWidget->setStyleSheet("border-top: 1px solid rgb(211, 211, 211);");
}

void AdminPage::itemsMenuVerticalLayout()
{

    QWidget* centralWidget = new QWidget(this);
    QString styleSheet = QString("QToolTip {  color: #ffffff; background-color: #313541; border-style: solid; border-style: solid; border-color: transparent blue transparent transparent; }");
    qApp->setStyleSheet(styleSheet);

    QStringList menuItemsTooltips = {
        "Surveys",
        "Banners",
        "Languages",
        "Footer",
        "Social Networks",
        "Users",
        "IA",
        "Teams",
        "News Partners",
        "Advertising"
    };

    QStringList menuItemsNames = {
        "Surveys",
        "Banners",
        "Languages",
        "Footer",
        "Social Networks",
        "Users",
        "Information Architecture",
        "Teams",
        "News Partners",
        "Advertising"
    };

    for(int i = 0; i < menuItemsTooltips.size(); i++) {
        QIcon icon("../img/"+menuItemsTooltips[i]+".png");
        MenuButton* menuItemButton = new MenuButton(menuItemsNames[i], menuItemsTooltips[i], icon, centralWidget, this);

        QObject::connect(menuItemButton, &QPushButton::clicked, this, [this, menuItemButton]() {
            OnMenuItemClicked(menuItemButton);
        });


        itemsMenuVLayout->addWidget(menuItemButton);
    }

    /*
    for (const QString& item : menuItems) {
        QString tooltip = item;
        QIcon icon("../img/"+item+".png");
        MenuButton* menuItemButton = new MenuButton(item, tooltip, icon, centralWidget);

        QObject::connect(menuItemButton, &QPushButton::clicked, this, [this, menuItemButton]() {
            OnMenuItemClicked(menuItemButton);
        });



        itemsMenuVLayout->addWidget(menuItemButton);
    }
    */

    itemsMenuVLayout->setAlignment(Qt::AlignTop);

    addCategoryButton->setText("+ Add category");
    addCategoryButton->setMinimumSize(95, 20);
    addCategoryButton->setStyleSheet(" QPushButton { border: 2px dashed grey; color: black; font-size: 12px; } ");

    categoriesVLayout->setAlignment(Qt::AlignTop);
    categoriesVLayout->insertWidget(0, addCategoryButton.get());

    addSubcategoryButton->setText("+ Add subcategory");
    addSubcategoryButton->setMinimumSize(95, 20);
    addSubcategoryButton->setStyleSheet(" QPushButton { border: 2px dashed grey; color: black; font-size: 12px; } ");

    subcategoriesVLayout->setAlignment(Qt::AlignTop);
    subcategoriesVLayout->insertWidget(0, addSubcategoryButton.get());

    addTeamButton->setText("+ Add team");
    addTeamButton->setMinimumSize(95, 20);
    addTeamButton->setStyleSheet(" QPushButton { border: 2px dashed grey; color: black; font-size: 12px; } ");

    teamsVLayout->setAlignment(Qt::AlignTop);
    teamsVLayout->insertWidget(0, addTeamButton.get());

    itemsMenuVLayout->addSpacerItem(itemsMenuSpacer_1.get());
}

void AdminPage::primaryContentArea()
{
    contentArea = std::make_unique<QScrollArea>();

    contentArea->setStyleSheet("QScrollArea { \
                                border-top: 1px solid white; \
                                border-left: 2px solid rgb(211, 211, 211); \
                                border-bottom: white; \
                                border-right: white;}");
}

void AdminPage::appendCategories()
{
    auto future = std::async(std::launch::async, [](){
        return Client::getInstance().GetCategories();
    });

    categories = future.get();
    std::vector<QPushButton*> buttons(categories.size());

    for(auto& el : categories)
    {
        subcategories_map_id.insert(QString::fromStdString(el.getName()), el.getId());
    }

    std::transform(categories.begin(), categories.end(), buttons.begin(), [](const Category& category) {
        return (new QPushButton(QString::fromStdString(category.getName())));
    });

    for (auto* button : buttons) {
        QWidget* buttons_widget = new QWidget();
        QHBoxLayout* buttons_layout = new QHBoxLayout();
        QPushButton* context_menu_button = new QPushButton();

        button->setMinimumWidth(80);
        button->setStyleSheet("QPushButton {"
                              "border: 1px solid gray;"
                              "border-right: none;"
                              "border-radius: 3px;"
                              "padding: 5px;"
                              "font-weight: bold;"
                              "color: gray;"
                              "image: none;"
                              "}"
                              "QPushButton:hover {"
                              "color: red;"
                              "}");

        context_menu_button->setFixedWidth(15);
        context_menu_button->setContextMenuPolicy(Qt::CustomContextMenu);
        context_menu_button->setMenu(categoryCustomMenu.get());
        context_menu_button->setEnabled(false);
        context_menu_button->setStyleSheet("QPushButton {"
                                           "border: 1px solid gray;"
                                           "border-left: none;"
                                           "border-radius: 3px;"
                                           "padding: 5px;"
                                           "font-weight: bold;"
                                           "color: gray;"
                                           "text-align: right;"
                                           "}");

        connect(context_menu_button, &QPushButton::customContextMenuRequested, [=](const QPoint &pos) {
            categoryCustomMenu->exec(button->mapToGlobal(pos));
        });

        connect(context_menu_button, &QPushButton::clicked, this, &AdminPage::onCategoryClicked);

        connect(button, &QPushButton::clicked, this, &AdminPage::onCategoryClicked);

        buttons_layout->addWidget(button);
        buttons_layout->addWidget(context_menu_button);
        buttons_layout->setSpacing(0);

        buttons_widget->setLayout(buttons_layout);
        categoriesVLayout->insertWidget(1, buttons_widget);
    }

    categoriesVLayout->setSpacing(20);
    MenuButton::setCategoriesLayout(categoriesVLayout.get());
}

void AdminPage::appendSubcategories()
{
    auto future = std::async(std::launch::async, [](){
        return Client::getInstance().GetSubcategories();
    });

    const auto& subcategories = future.get();
    std::vector<QPushButton*> buttons(subcategories.size());

    for(auto& el : subcategories)
    {
        subcategories_map.insert(QString::fromStdString(el.getName()), el.getCategoryId());
        subcategories_map_id.insert(QString::fromStdString(el.getName()), el.getId());
    }

    std::transform(subcategories.begin(), subcategories.end(), buttons.begin(), [](const Subcategory& subcategory) {
        return (new QPushButton(QString::fromStdString(subcategory.getName())));
    });

    for (auto* button : buttons) {
        QWidget* buttons_widget = new QWidget();
        QHBoxLayout* buttons_layout = new QHBoxLayout();
        QPushButton* context_menu_button = new QPushButton();

        button->setMinimumWidth(80);
        button->setStyleSheet("QPushButton {"
                              "border: 1px solid gray;"
                              "border-right: none;"
                              "border-radius: 3px;"
                              "padding: 5px;"
                              "font-weight: bold;"
                              "color: gray;"
                              "image: none;"
                              "}"
                              "QPushButton:hover {"
                              "color: red;"
                              "}");

        context_menu_button->setFixedWidth(15);
        context_menu_button->setContextMenuPolicy(Qt::CustomContextMenu);
        context_menu_button->setMenu(contextMenu.get());
        context_menu_button->setEnabled(false);
        context_menu_button->setStyleSheet("QPushButton {"
                                           "border: 1px solid gray;"
                                           "border-left: none;"
                                           "border-radius: 3px;"
                                           "padding: 5px;"
                                           "font-weight: bold;"
                                           "color: gray;"
                                           "text-align: right;"
                                           "}");

        connect(context_menu_button, &QPushButton::customContextMenuRequested, [=](const QPoint &pos) {
            contextMenu->exec(button->mapToGlobal(pos));
        });

        connect(context_menu_button, &QPushButton::clicked, this, &AdminPage::onSubcategoryClicked);

        connect(button, &QPushButton::clicked, this, &AdminPage::onSubcategoryClicked);

        buttons_layout->addWidget(button);
        buttons_layout->addWidget(context_menu_button);
        buttons_layout->setSpacing(0);

        buttons_widget->setLayout(buttons_layout);
        buttons_widget->hide();
        subcategoriesVLayout->insertWidget(1, buttons_widget);
    }

    MenuButton::setSubcategoriesLayout(subcategoriesVLayout.get());
}

void AdminPage::appendTeams()
{
    auto future = std::async(std::launch::async, [](){
        return Client::getInstance().GetTeams();
    });

    auto teams = future.get();
    std::vector<QPushButton*> buttons(teams.size());

    for(auto& el : teams)
    {
        teams_map.insert(el.getTeamName(), el.getSubcategoryId());
        teams_map_id.insert(el.getTeamName(), el.getTeamId());
    }


    std::transform(teams.begin(), teams.end(), buttons.begin(), [](Team& team) {
        return (new QPushButton(team.getTeamName()));
    });

    for (auto* button : buttons) {
        QWidget* buttons_widget = new QWidget();
        QHBoxLayout* buttons_layout = new QHBoxLayout();
        QPushButton* context_menu_button = new QPushButton();

        button->setMinimumWidth(80);
        button->setStyleSheet("QPushButton {"
                              "border: 1px solid gray;"
                              "border-right: none;"
                              "border-radius: 3px;"
                              "padding: 5px;"
                              "font-weight: bold;"
                              "color: gray;"
                              "image: none;"
                              "}"
                              "QPushButton:hover {"
                              "color: red;"
                              "}");

        context_menu_button->setFixedWidth(15);
        context_menu_button->setContextMenuPolicy(Qt::CustomContextMenu);
        context_menu_button->setMenu(teamContextMenu.get());
        context_menu_button->setEnabled(false);
        context_menu_button->setStyleSheet("QPushButton {"
                                           "border: 1px solid gray;"
                                           "border-left: none;"
                                           "border-radius: 3px;"
                                           "padding: 5px;"
                                           "font-weight: bold;"
                                           "color: gray;"
                                           "text-align: right;"
                                           "}");

        connect(context_menu_button, &QPushButton::customContextMenuRequested, [=](const QPoint &pos) {
            contextMenu->exec(button->mapToGlobal(pos));
        });

        connect(context_menu_button, &QPushButton::clicked, this, &AdminPage::onTeamClicked);
        connect(button, &QPushButton::released, this, &AdminPage::onTeamClicked);

        buttons_layout->addWidget(button);
        buttons_layout->addWidget(context_menu_button);
        buttons_layout->setSpacing(0);

        buttons_widget->setLayout(buttons_layout);
        buttons_widget->hide();
        teamsVLayout->insertWidget(1, buttons_widget);
    }

    MenuButton::setTeamsLayout(teamsVLayout.get());
}

bool AdminPage::checkIfStringEmpty(const QString &temp_string)
{
    return (temp_string == "");
}

void AdminPage::createSaveChangesButton(const QString& PageName)
{

    // Видаляємо всі попередні зв'язки для події clicked
    saveChangesButton->disconnect(SIGNAL(clicked()));

    // Змінюємо текст і стиль існуючого saveChangesButton в залежності від PageName
    if (PageName == "Information Architecture")
    {
        saveChangesButton->setText("Save");
        saveChangesButton->setStyleSheet("QPushButton { \
                                          background-color: rgb(208, 0, 0); \
                                          color: rgb(255, 255, 255); border:none}");
        connect(saveChangesButton.get(), &QPushButton::clicked, this, &AdminPage::on_save_changes_clicked);
    }
    else if (PageName == "Teams")
    {
        saveChangesButton->setText("+Add Team");
        saveChangesButton->setStyleSheet("QPushButton { \
                                          background-color: rgb(208, 0, 0); \
                                          color: rgb(255, 255, 255); border:none}");
        connect(saveChangesButton.get() ,&QPushButton::clicked , this,&AdminPage::handleTeamsClicked);
    }
    else
    {
        saveChangesButton->setText("Other");
        saveChangesButton->setStyleSheet("QPushButton { \
                                          background-color: rgb(208, 0, 0); \
                                          color: rgb(255, 255, 255); border:none}");
    }
}

void AdminPage::handleTeamsClicked()
{
    MenuButton::addTeamButtonClicked();
}


void AdminPage::onLogoutDone() {
    this->close();
}

void AdminPage::on_add_category_clicked()
{
    addCategoryWindow->setModal(true);
    addCategoryWindow->show();
}

void AdminPage::on_add_subcategory_clicked()
{
    if(tempCategoryId != NULL)
    {
        addSubcategoryWindow->setModal(true);
        addSubcategoryWindow->show();
    }
    else { QMessageBox::warning(this, "CategoryError", "You need to choose some category first or save a new one!"); }
}

void AdminPage::on_add_team_clicked()
{

    if(tempSubcategoryId != NULL)
    {
        addTeamWindow->setModal(true);
        addTeamWindow->show();
    }
    else { QMessageBox::warning(this, "TeamError", "You need to choose some team first or save a new one!"); }
}

void AdminPage::on_save_changes_clicked()
{
    int count = 0;

    if(!checkIfStringEmpty(tempCategory))
    {
        Client::getInstance().PostCategory(tempCategory.toStdString());
        tempCategory = "";
        count++;
    }

    if((!checkIfStringEmpty(tempSubcategory)) and (tempCategoryId != NULL))
    {
        subcategories_map_id.insert(tempSubcategory, Client::getInstance().GetSubcategories().at(Client::getInstance().GetSubcategories().size() - 1).getId());
        Client::getInstance().PostSubcategory(tempSubcategory.toStdString(), tempCategoryId);
        tempSubcategory = "";
        count++;
    }

    if((!checkIfStringEmpty(tempTeam)) and (tempSubcategoryId != NULL))
    {
        Team team;

        team.setTeamName(tempTeam);
        team.setTeamId(tempTeamId);
        team.setSubcategoryId(tempSubcategoryId);

        teams_map_id.insert(tempTeam, Client::getInstance().GetTeams().at(Client::getInstance().GetTeams().size() - 1).getTeamId());
        Client::getInstance().PostTeam(team);
        tempTeam = "";
        count++;
    }

    if(count != 0)
    {
        QMessageBox::information(this, "SaveSuccess", "All changes succesfully saved!");
    }
}

void AdminPage::handleNewButtonAdded()
{
    tempCategory = addCategoryWindow->getCategoryName();

    if(!checkIfStringEmpty(tempCategory))
    {
        QPushButton* newButton = new QPushButton(tempCategory);
        QWidget* buttons_widget = new QWidget();
        QHBoxLayout* buttons_layout = new QHBoxLayout();
        QPushButton* context_menu_button = new QPushButton();

        newButton->setMinimumWidth(80);
        newButton->setStyleSheet("QPushButton {"
                                 "border: 1px solid gray;"
                                 "border-right: none;"
                                 "border-radius: 3px;"
                                 "padding: 5px;"
                                 "font-weight: bold;"
                                 "color: gray;"
                                 "}"
                                 "QPushButton:hover {"
                                 "color: red;"
                                 "}");

        context_menu_button->setFixedWidth(15);
        context_menu_button->setContextMenuPolicy(Qt::CustomContextMenu);
        context_menu_button->setMenu(contextMenu.get());
        context_menu_button->setEnabled(false);
        context_menu_button->setStyleSheet("QPushButton {"
                                           "border: 1px solid gray;"
                                           "border-left: none;"
                                           "border-radius: 3px;"
                                           "padding: 5px;"
                                           "font-weight: bold;"
                                           "color: gray;"
                                           "}");

        subcategories_map.insert(tempSubcategory, tempCategoryId);

        buttons_layout->addWidget(newButton);
        buttons_layout->addWidget(context_menu_button);
        buttons_layout->setSpacing(0);

        connect(newButton, &QPushButton::clicked, this, &AdminPage::onCategoryClicked);

        connect(context_menu_button, &QPushButton::customContextMenuRequested, [=](const QPoint &pos) {
            contextMenu->exec(context_menu_button->mapToGlobal(pos));
        });

        buttons_widget->setLayout(buttons_layout);
        categoriesVLayout->insertWidget(1, buttons_widget);
        tempCategoryId = NULL;
    }
}

void AdminPage::handleNewSubcategoryAdded()
{
    tempSubcategory = addSubcategoryWindow->getSubcategoryName();

    if(!checkIfStringEmpty(tempSubcategory))
    {
        QPushButton* newButton = new QPushButton(tempSubcategory);
        QWidget* buttons_widget = new QWidget();
        QHBoxLayout* buttons_layout = new QHBoxLayout();
        QPushButton* context_menu_button = new QPushButton();

        newButton->setMinimumWidth(80);
        newButton->setStyleSheet("QPushButton {"
                                 "border: 1px solid gray;"
                                 "border-right: none;"
                                 "border-radius: 3px;"
                                 "padding: 5px;"
                                 "font-weight: bold;"
                                 "color: gray;"
                                 "}"
                                 "QPushButton:hover {"
                                 "color: red;"
                                 "}");

        context_menu_button->setFixedWidth(15);
        context_menu_button->setContextMenuPolicy(Qt::CustomContextMenu);
        context_menu_button->setMenu(contextMenu.get());
        context_menu_button->setEnabled(false);
        context_menu_button->setStyleSheet("QPushButton {"
                                           "border: 1px solid gray;"
                                           "border-left: none;"
                                           "border-radius: 3px;"
                                           "padding: 5px;"
                                           "font-weight: bold;"
                                           "color: gray;"
                                           "}");

        subcategories_map.insert(tempSubcategory, tempCategoryId);

        buttons_layout->addWidget(newButton);
        buttons_layout->addWidget(context_menu_button);
        buttons_layout->setSpacing(0);

        connect(newButton, &QPushButton::clicked, this, &AdminPage::onSubcategoryClicked);

        connect(context_menu_button, &QPushButton::customContextMenuRequested, [=](const QPoint &pos) {
            contextMenu->exec(context_menu_button->mapToGlobal(pos));
        });

        buttons_widget->setLayout(buttons_layout);
        subcategoriesVLayout->insertWidget(1, buttons_widget);
    }
}


void AdminPage::handleNewTeamAdded()
{
    tempTeam = addTeamWindow->getTeamName();

    if(!checkIfStringEmpty(tempTeam))
    {
        QPushButton* newButton = new QPushButton(tempTeam);
        QWidget* buttons_widget = new QWidget();
        QHBoxLayout* buttons_layout = new QHBoxLayout();
        QPushButton* context_menu_button = new QPushButton();

        newButton->setMinimumWidth(80);
        newButton->setStyleSheet("QPushButton {"
                                 "border: 1px solid gray;"
                                 "border-right: none;"
                                 "border-radius: 3px;"
                                 "padding: 5px;"
                                 "font-weight: bold;"
                                 "color: gray;"
                                 "}"
                                 "QPushButton:hover {"
                                 "color: red;"
                                 "}");

        context_menu_button->setFixedWidth(15);
        context_menu_button->setContextMenuPolicy(Qt::CustomContextMenu);
        context_menu_button->setMenu(teamContextMenu.get());
        context_menu_button->setEnabled(false);
        context_menu_button->setStyleSheet("QPushButton {"
                                           "border: 1px solid gray;"
                                           "border-left: none;"
                                           "border-radius: 3px;"
                                           "padding: 5px;"
                                           "font-weight: bold;"
                                           "color: gray;"
                                           "}");

        teams_map.insert(tempTeam, tempSubcategoryId);

        buttons_layout->addWidget(newButton);
        buttons_layout->addWidget(context_menu_button);
        buttons_layout->setSpacing(0);

        connect(newButton, &QPushButton::clicked, this, &AdminPage::onTeamClicked);

        connect(context_menu_button, &QPushButton::customContextMenuRequested, [=](const QPoint &pos) {
            contextMenu->exec(context_menu_button->mapToGlobal(pos));
        });

        buttons_widget->setLayout(buttons_layout);
        teamsVLayout->insertWidget(1, buttons_widget);
    }
}

void AdminPage::OnMenuItemClicked(MenuButton*menuItemButton)
{
    menuHWidget->resetCurrentCategory();
    pageLabel->setText(menuItemButton->GetItemName());
    createSaveChangesButton(menuItemButton->GetItemName());
    handleMenuItemClick(menuItemButton, contentArea.get());

}

void AdminPage::onCategorySelected(Category *category)
{
    pageLabel->setText(QString::fromStdString(category->getName()));
    qDebug() << "Category: " << category->getName() << "\n";
}

void AdminPage::onCategoryClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    QWidget* category_widget = clickedButton->parentWidget();

    clickedButton->setStyleSheet("QPushButton {"
                                 "border: 1px solid gray;"
                                 "border-right: none;"
                                 "border-radius: 3px;"
                                 "padding: 5px;"
                                 "font-weight: bold;"
                                 "color: red;"
                                 "}");


    if (previousButton != nullptr)
    {
        previousButton->setStyleSheet("QPushButton {"
                                      "border: 1px solid gray;"
                                      "border-right: none;"
                                      "border-radius: 3px;"
                                      "padding: 5px;"
                                      "font-weight: bold;"
                                      "color: gray;"
                                      "image: none;"
                                      "}"
                                      "QPushButton:hover {"
                                      "color: red;"
                                      "}");

        qobject_cast<QPushButton*>(previousButton->parentWidget()->layout()->itemAt(1)->widget())->setEnabled(false);
    }

    previousButton = clickedButton;
    tempSubcategoryId = categories_map_id[clickedButton->text()];

    for(const auto& el : categories)
    {
        if(el.getName() == clickedButton->text().toStdString())
        {
            tempCategoryId = el.getId();
            break;
        }
    }

    for(int i = 1; i < subcategoriesVLayout->count(); i++)
    {
        QPushButton* button = qobject_cast<QPushButton*>(subcategoriesVLayout->itemAt(i)->widget()->layout()->itemAt(0)->widget());
        QPushButton* context_menu_button = qobject_cast<QPushButton*>(subcategoriesVLayout->itemAt(i)->widget()->layout()->itemAt(1)->widget());
        QWidget* subcategories_widget = qobject_cast<QWidget*>(subcategoriesVLayout->itemAt(i)->widget());

        if(subcategories_map[button->text()] == tempCategoryId)
        {
            if(tempCategoryId == NULL)
            {
                subcategories_widget->hide();
            }
            else { subcategories_widget->show(); };
        }
        else { subcategories_widget->hide(); }
    }

    qobject_cast<QPushButton*>(category_widget->layout()->itemAt(1)->widget())->setEnabled(true);
    CategoryCustomMenu::setTempCategoryButton(clickedButton);
    CategoryCustomMenu::setCategoryIndex(tempCategoryId);
}

void AdminPage::onSubcategoryClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    QWidget* subcategory_widget = clickedButton->parentWidget();

    clickedButton->setStyleSheet("QPushButton {"
                                 "border: 1px solid gray;"
                                 "border-right: none;"
                                 "border-radius: 3px;"
                                 "padding: 5px;"
                                 "font-weight: bold;"
                                 "color: red;"
                                 "}");

    if (previousSubcategory != nullptr)
    {
        previousSubcategory->setStyleSheet("QPushButton {"
                                      "border: 1px solid gray;"
                                      "border-right: none;"
                                      "border-radius: 3px;"
                                      "padding: 5px;"
                                      "font-weight: bold;"
                                      "color: gray;"
                                      "image: none;"
                                      "}"
                                      "QPushButton:hover {"
                                      "color: red;"
                                      "}");
        qobject_cast<QPushButton*>(previousSubcategory->parentWidget()->layout()->itemAt(1)->widget())->setEnabled(false);
    }

    previousSubcategory = clickedButton;
    tempSubcategoryId = subcategories_map_id[clickedButton->text()];
    tempTeamId = teams_map_id[clickedButton->text()];

    for(int i = 1; i < teamsVLayout->count(); i++)
    {
        QPushButton* button = qobject_cast<QPushButton*>(teamsVLayout->itemAt(i)->widget()->layout()->itemAt(0)->widget());
        QPushButton* context_menu_button = qobject_cast<QPushButton*>(teamsVLayout->itemAt(i)->widget()->layout()->itemAt(1)->widget());
        QWidget* teams_widget = qobject_cast<QWidget*>(teamsVLayout->itemAt(i)->widget());

        if(teams_map[button->text()] == tempSubcategoryId)
        {
            if(tempSubcategoryId == NULL)
            {
                teams_widget->hide();
            }
            else
            {
                teams_widget->show();
            };

        }
        else { teams_widget->hide(); }
    }

    qobject_cast<QPushButton*>(subcategory_widget->layout()->itemAt(1)->widget())->setEnabled(true);
    CustomContextMenu::setTempSubcategoryButton(clickedButton);
    CustomContextMenu::setSubcategoryIndex(tempSubcategoryId);
}

void AdminPage::onTeamClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    QWidget* team_widget = clickedButton->parentWidget();

    clickedButton->setStyleSheet("QPushButton {"
                                 "border: 1px solid gray;"
                                 "border-right: none;"
                                 "border-radius: 3px;"
                                 "padding: 5px;"
                                 "font-weight: bold;"
                                 "color: red;"
                                 "}");

    if (previousTeam != nullptr)
    {
        previousTeam->setStyleSheet("QPushButton {"
                                           "border: 1px solid gray;"
                                           "border-right: none;"
                                           "border-radius: 3px;"
                                           "padding: 5px;"
                                           "font-weight: bold;"
                                           "color: gray;"
                                           "image: none;"
                                           "}"
                                           "QPushButton:hover {"
                                           "color: red;"
                                           "}");
        qobject_cast<QPushButton*>(previousTeam->parentWidget()->layout()->itemAt(1)->widget())->setEnabled(false);
    }

    previousTeam = clickedButton;
    tempTeamId = teams_map_id[clickedButton->text()];

    qobject_cast<QPushButton*>(team_widget->layout()->itemAt(1)->widget())->setEnabled(true);
    TeamContextMenu::setTempTeamButton(clickedButton);
    TeamContextMenu::setTeamIndex(tempTeamId);
}

void AdminPage::resizeEvent(QResizeEvent *event)
{
    emit adminPageResized();
    qDebug() << "Admin Resized";

    QWidget::resizeEvent(event);
}
