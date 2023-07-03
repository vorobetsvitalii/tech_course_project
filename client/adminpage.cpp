#include "adminpage.h"
#include "ui_adminpage.h"
#include <functional>

AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    this->resize(620, 579);
    this->setWindowTitle("Sports Hub");
    this->setStyleSheet("QWidget {background-color: rgb(255, 255, 255); }");

    addCategoryWindow = std::make_unique<AddCategory>();

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

    appendCategories();

    genericGridLayout->addWidget(topHWidget.get(), 0, 0); // Generic grid layout forming
    genericGridLayout->addLayout(configurationHLayout.get(), 1, 0);
    genericGridLayout->addWidget(menuHWidget.get(), 2, 0);
    genericGridLayout->addLayout(localNavigationLayout.get(), 3, 0);

    genericGridLayout->setContentsMargins(0, 0, 0, 0);

    connect(&Client::getInstance(), &Client::logoutDoneEvent, this, &AdminPage::onLogoutDone);
    connect(addCategoryButton.get(), &QPushButton::clicked, this, &AdminPage::on_add_category_clicked);
    connect(addCategoryWindow.get(), &AddCategory::newButtonAdded, this, &AdminPage::handleNewButtonAdded);
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
    //menuHLayout = std::make_unique<QHBoxLayout>();
    localNavigationLayout = std::make_unique<QHBoxLayout>();
    itemsMenuVLayout = std::make_unique<QVBoxLayout>();
    categoriesVLayout = std::make_unique<QVBoxLayout>();
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
    topHLayout->addWidget(switchButtonWidget.get());
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

    saveChangesButton->setText("Save all changes");
    saveChangesButton->setFixedSize(100, 30);
    saveChangesButton->setStyleSheet("QPushButton { \
                                      background-color: rgb(208, 0, 0); \
                                      color: rgb(255, 255, 255); border:none}");

    QFont homeLabelFont("Open Sans", 16, QFont::Bold);

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

    QStringList menuItems = {
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

    for (const QString& item : menuItems) {
        QString tooltip = item;
        QIcon icon("../img/"+item+".png");
        MenuButton* menuItemButton = new MenuButton(item, tooltip, icon, centralWidget);

        QObject::connect(menuItemButton, &QPushButton::clicked, this, [this, menuItemButton]() {
            OnMenuItemClicked(menuItemButton);
        });



        itemsMenuVLayout->addWidget(menuItemButton);
    }

    itemsMenuVLayout->setAlignment(Qt::AlignTop);


    addCategoryButton->setText("+ Add category");
    addCategoryButton->setMinimumSize(95, 20);
    addCategoryButton->setStyleSheet(" QPushButton { border: 2px dashed grey; color: black; font-size: 12px; } ");

    categoriesVLayout->insertWidget(0, addCategoryButton.get());
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
        return Client::getInstance().GetCategoties();
    });

    const auto& categories = future.get();
    std::vector<QPushButton*> buttons(categories.size());

    std::transform(categories.begin(), categories.end(), buttons.begin(), [](const Category& category) {
        return new QPushButton(QString::fromStdString(category.getName()));
    });

    for (auto* button : buttons) {
        categoriesVLayout->insertWidget(1, button);
    }
}

void AdminPage::onLogoutDone() {
    this->close();
}

void AdminPage::on_add_category_clicked()
{
    addCategoryWindow->show();
}

void AdminPage::handleNewButtonAdded()
{
    QPushButton* newButton = new QPushButton(addCategoryWindow->getCategoryName());

    categoriesVLayout->insertWidget(1, newButton);
    Client::getInstance().PostCategories(addCategoryWindow->getCategoryName().toStdString());
}

void AdminPage::OnMenuItemClicked(MenuButton*menuItemButton)
{
    handleMenuItemClick(menuItemButton, contentArea.get());
}

void AdminPage::onCategorySelected(Category *category)
{
   // обробка вибраної сторінки
    qDebug() << "Category: " << category->getName() << "\n";
}
