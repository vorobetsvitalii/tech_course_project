#include "adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    this->resize(620, 579);
    this->setWindowTitle("Sports Hub");
    this->setStyleSheet("QWidget {background-color: rgb(255, 255, 255); }");

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
    localNavigationLayout->addLayout(categoriesVLayout.get());
    localNavigationLayout->addWidget(contentArea.get());

    genericGridLayout->addWidget(topHWidget.get(), 0, 0); // Generic grid layout forming
    genericGridLayout->addLayout(configurationHLayout.get(), 1, 0);
    genericGridLayout->addWidget(menuHWidget.get(), 2, 0);
    genericGridLayout->addLayout(localNavigationLayout.get(), 3, 0);

    connect(&Client::getInstance(), &Client::logoutDoneEvent, this, &AdminPage::onLogoutDone);

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
    menuHLayout = std::make_unique<QHBoxLayout>();
    localNavigationLayout = std::make_unique<QHBoxLayout>();
    itemsMenuVLayout = std::make_unique<QVBoxLayout>();
    categoriesVLayout = std::make_unique<QVBoxLayout>();
}

void AdminPage::initializeWidgets()
{
    topHWidget = std::make_unique<QWidget>();
    switchButtonWidget = std::make_unique<QWidget>();
    menuHWidget = std::make_unique<QWidget>();
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
    addCategoriesButton = std::make_unique<QPushButton>();
    pushButton_1 = std::make_unique<QPushButton>();
    pushButton_2 = std::make_unique<QPushButton>();
    pushButton_3 = std::make_unique<QPushButton>();
    pushButton_4 = std::make_unique<QPushButton>();
    pushButton_5 = std::make_unique<QPushButton>();
    pushButton_6 = std::make_unique<QPushButton>();
    pushButton_7 = std::make_unique<QPushButton>();
    pushButton_8 = std::make_unique<QPushButton>();
    pushButton_9 = std::make_unique<QPushButton>();
}

void AdminPage::initializeSpacers()
{
    // Top layout
    topSpacer_1 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    topSpacer_2 = std::make_unique<QSpacerItem>(25, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Configuration layout
    configSpacer_1 = std::make_unique<QSpacerItem>(60, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    configSpacer_2 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    configSpacer_3 = std::make_unique<QSpacerItem>(9, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    configSpacer_4 = std::make_unique<QSpacerItem>(15, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Menu layout
    menuSpacer_1 = std::make_unique<QSpacerItem>(52, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    menuSpacer_2 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    // Items menu layout
    itemsMenuSpacer_1 = std::make_unique<QSpacerItem>(20, 30, QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Primary content area
    localNavigationSpacer_1 = std::make_unique<QSpacerItem>(15, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void AdminPage::topHorizontalLayout()
{
    QFont homepagePushButtonFont("Tahoma", 12);
    QString projectPath = QCoreApplication::applicationDirPath();

    homepagePushButton->setText("Sports Hub");
    homepagePushButton->setFixedSize(150, 50);
    homepagePushButton->setFont(homepagePushButtonFont);
    homepagePushButton->setStyleSheet("QPushButton { \
                                       background-color: rgb(208, 0, 0); \
                                       color: rgb(255, 255, 255); \
                                       border:none;}");

    switchPushButton->setStyleSheet("QPushButton { \
                                     border: none; background-color: rgb(216, 223, 233); \
                                     margin-left: 10px;}");

    switchPushButton->setIcon(QIcon(projectPath.replace("build-client-Desktop_Qt_6_5_0_MinGW_64_bit-Debug", "img/switchIcon.png")));
    switchPushButton->setIconSize(QSize(35, 40));

    topHLayout->addWidget(homepagePushButton.get());
    topHLayout->addSpacerItem(topSpacer_1.get());
    topHLayout->addWidget(switchButtonWidget.get());
    topHLayout->addSpacerItem(topSpacer_2.get());
    topHLayout->addWidget(adminInfoWidget.get());
    topHWidget->setLayout(topHLayout.get());
}

void AdminPage::configurationHorizontalLayout()
{
    cancelPushButton->setText("\"Cancel\"");
    cancelPushButton->resize(56, 20);
    cancelPushButton->setStyleSheet("QPushButton { \
                                     background-color: rgb(255, 255, 255); \
                                     color: rgb(255, 0, 0); border:none}");

    saveChangesButton->setText("Save all changes");
    saveChangesButton->setFixedSize(100, 30);
    saveChangesButton->setStyleSheet("QPushButton { \
                                      background-color: rgb(208, 0, 0); \
                                      color: rgb(255, 255, 255); border:none}");

    QFont homeLabelFont("Tahoma", 16, QFont::Bold);

    homeLabel = std::make_unique<QLabel>();

    homeLabel->setText("Home");
    homeLabel->setFont(homeLabelFont);

    configurationHLayout->addSpacerItem(configSpacer_1.get());
    configurationHLayout->addWidget(homeLabel.get());
    configurationHLayout->addSpacerItem(configSpacer_2.get());
    configurationHLayout->addWidget(cancelPushButton.get());
    configurationHLayout->addSpacerItem(configSpacer_3.get());
    configurationHLayout->addWidget(saveChangesButton.get());
    configurationHLayout->addSpacerItem(configSpacer_4.get());
}

void AdminPage::menuHorizontalLayout()
{
    QFont homePushButtonFont("Tahoma", 10, QFont::Bold);

    homePushButton->setFont(homePushButtonFont);
    homePushButton->setText("HOME");
    homePushButton->setStyleSheet("QPushButton { \
                                   border: none; background-color: \
                                   rgb(255, 255, 255); \
                                   color: rgb(255, 0, 0);}");

    menuHLayout->addSpacerItem(menuSpacer_1.get());
    menuHLayout->addWidget(homePushButton.get());
    menuHLayout->addSpacerItem(menuSpacer_2.get());

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(menuHWidget.get());

    shadowEffect->setBlurRadius(8);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    shadowEffect->setOffset(0, 4);

    menuHWidget->setLayout(menuHLayout.get());
    menuHWidget->setGraphicsEffect(shadowEffect);
    menuHWidget->setStyleSheet("border-left: white; \
                                border-right: white; \
                                border-top: 2px solid rgb(211, 211, 211); \
                                border-bottom: 2px solid rgb(211, 211, 211);");
}

void AdminPage::itemsMenuVerticalLayout()
{
    pushButton_1->setStyleSheet("margin-bottom: 5px;");
    pushButton_2->setStyleSheet("margin-bottom: 5px;");
    pushButton_3->setStyleSheet("margin-bottom: 5px;");
    pushButton_4->setStyleSheet("margin-bottom: 5px;");
    pushButton_5->setStyleSheet("margin-bottom: 5px;");
    pushButton_6->setStyleSheet("margin-bottom: 5px;");
    pushButton_7->setStyleSheet("margin-bottom: 5px;");
    pushButton_8->setStyleSheet("margin-bottom: 5px;");
    pushButton_9->setStyleSheet("margin-bottom: 5px;");

    itemsMenuVLayout->addWidget(pushButton_1.get());
    itemsMenuVLayout->addWidget(pushButton_2.get());
    itemsMenuVLayout->addWidget(pushButton_3.get());
    itemsMenuVLayout->addWidget(pushButton_4.get());
    itemsMenuVLayout->addWidget(pushButton_5.get());
    itemsMenuVLayout->addWidget(pushButton_6.get());
    itemsMenuVLayout->addWidget(pushButton_7.get());
    itemsMenuVLayout->addWidget(pushButton_8.get());
    itemsMenuVLayout->addWidget(pushButton_9.get());

    addCategoriesButton->setText("+ Add category");
    addCategoriesButton->setMinimumSize(90, 20);
    addCategoriesButton->setStyleSheet(" QPushButton { border: 2px dashed grey; color: black; font-size: 10px; } ");

    categoriesVLayout->insertWidget(0, addCategoriesButton.get());
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

void AdminPage::onLogoutDone() {
    this->close();
}
