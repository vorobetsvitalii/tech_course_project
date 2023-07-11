#include "teamsui.h"

void TeamsUI::initializeLocationDrop()
{
    LocationDrop = std::make_unique<QComboBox>();




    LocationDrop->setFixedSize(246,36);
    QString comboBoxStyle = "QComboBox {"
                            "background-color: white;"
                            "color: black;"
                            "border: 1px solid rgba(212, 217, 226, 1);"
                            "min-width: 246px;"
                            "min-height: 36px;"
                            "}"
                            "QComboBox::drop-down {"
                            "border: none;"
                            "}"
                            "QComboBox::down-arrow {"
                            "image: url(../img/TeamArrow.png);"
                            "height: 5px;"
                            "width: 7px;"
                            "}"
                            "QListView::item {"
                            "max-width: 240px;"
                            "min-height: 36px;"
                            "border: none;"
                            "outline: 0px;"
                            "}";


    LocationDrop->setStyleSheet(comboBoxStyle);
    QListView * listView = new QListView();
    listView->setStyleSheet("QListView::item {"
                            "max-width: 246px;"
                            "min-height: 36px;"
                            "border:none;"
                            "}"
                            "QListView::item:selected {"
                            "border-color:white;"
                            "background-color: rgba(215, 33, 48, 0.11);"
                            "color: rgba(215, 33, 48, 1);"
                            "outline: 0px;"
                            "}"
                            "QListView::item:hover {"
                            "outline: 0px;"
                            "border: 1px solid rgba(215, 33, 48, 0.11);"
                            "}");

    //listView->setFixedSize(250,36);

    LocationDrop->setView(listView);
    LocationDrop->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    LocationDrop->view()->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    LocationDrop->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    LocationDrop->view()->style()->setProperty("hoverHighlight", false);
    for (const auto& tmp : this->LocationMap) {
        LocationDrop->addItem(QString::fromStdString(tmp.second));
    }

}

void TeamsUI::initializeCategoryDrop()
{
    CategoryDrop = std::make_unique<QComboBox>();
    this->CategoriesMap = GetCategories();
    CategoryDrop->setFixedSize(246,36);

    //не забути про стрілку
    QString comboBoxStyle = "QComboBox {"
                            "background-color: white;"
                            "color: black;"
                            "border: 1px solid rgba(212, 217, 226, 1);"
                            "min-width: 246px;"
                            "min-height: 36px;"
                            "}"
                            "QComboBox::drop-down {"
                            "border: none;"
                            "}"
                            "QComboBox::down-arrow {"
                            "image: url(../img/TeamArrow.png);"
                            "height: 5px;"
                            "width: 7px;"
                            "}"
                            "QListView::item {"
                            "max-width: 240px;"
                            "min-height: 36px;"
                            "border: none;"
                            "outline: 0px;"
                            "}";


    CategoryDrop->setStyleSheet(comboBoxStyle);
    QListView * listView = new QListView();
    listView->setStyleSheet("QListView::item {"
                            "max-width: 246px;"
                            "min-height: 36px;"
                            "border:none;"
                            "}"
                            "QListView::item:selected {"
                            "border-color:white;"
                            "background-color: rgba(215, 33, 48, 0.11);"
                            "color: rgba(215, 33, 48, 1);"
                            "outline: 0px;"
                            "}"
                            "QListView::item:hover {"
                            "outline: 0px;"
                            "border: 1px solid rgba(215, 33, 48, 0.11);"
                            "}");

    //listView->setFixedSize(250,36);

    CategoryDrop->setView(listView);
    CategoryDrop->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    CategoryDrop->view()->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    CategoryDrop->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    CategoryDrop->view()->style()->setProperty("hoverHighlight", false);
    for (const auto& tmp : this->CategoriesMap) {
        CategoryDrop->addItem(QString::fromStdString(tmp.second));
    }
}

void TeamsUI::initializeSubCategoryDrop()
{
    SubCategoryDrop = std::make_unique<QComboBox>();
    QStringList SubCategoryList; //додати зчитування з БД підкатегорій!
    SubCategoryDrop->addItem("All");
    SubCategoryList << "Football" << "Dog Sledding" << "Baseball" << "Basketball" << "Surfing" << "Skiing"
                 << "Golf" << "Fishing" << "Handball" << "Cornhole";

    SubCategoryDrop->setFixedSize(246,36);
    QString comboBoxStyle = "QComboBox {"
                            "background-color: white;"
                            "color: black;"
                            "border: 1px solid rgba(212, 217, 226, 1);"
                            "min-width: 246px;"
                            "min-height: 36px;"
                            "}"
                            "QComboBox::drop-down {"
                            "border: none;"
                            "}"
                            "QComboBox::down-arrow {"
                            "image: url(../img/TeamArrow.png);"
                            "height: 5px;"
                            "width: 7px;"
                            "}"
                            "QListView::item {"
                            "max-width: 240px;"
                            "min-height: 36px;"
                            "border: none;"
                            "outline: 0px;"
                            "}";


    SubCategoryDrop->setStyleSheet(comboBoxStyle);
    QListView * listView = new QListView();
    listView->setStyleSheet("QListView::item {"
                            "max-width: 246px;"
                            "min-height: 36px;"
                            "border:none;"
                            "}"
                            "QListView::item:selected {"
                            "border-color:white;"
                            "background-color: rgba(215, 33, 48, 0.11);"
                            "color: rgba(215, 33, 48, 1);"
                            "outline: 0px;"
                            "}"
                            "QListView::item:hover {"
                            "outline: 0px;"
                            "border: 1px solid rgba(215, 33, 48, 0.11);"
                            "}");

    //listView->setFixedSize(250,36);

    SubCategoryDrop->setView(listView);
    SubCategoryDrop->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    SubCategoryDrop->view()->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    SubCategoryDrop->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    SubCategoryDrop->view()->style()->setProperty("hoverHighlight", false);
    for(auto tmp : SubCategoryList){
        SubCategoryDrop->addItem(tmp);
    }
}

void TeamsUI::initializeTeamInput()
{
    TeamInput = std::make_unique<QLineEdit>();
    TeamInput->setPlaceholderText(QString("Name of team or player"));
    TeamInput->setFont(QFont("Open Sans"));
    TeamInput->setStyleSheet("QLinedit{ background-color:white; }");
    TeamInput->setFixedSize(246,36);

}

void TeamsUI::initializeApplyButton()
{
    ApplyButton = std::make_unique<QPushButton>();
    ApplyButton->setText("Apply");
    ApplyButton->setFixedSize(246,32);
    ApplyButton->setStyleSheet("QPushButton {"
                               "background-color: rgba(247, 211, 214, 1);"
                               "color: white;"
                               "border: 0px;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: rgba(224, 34, 50, 1);"
                               "}"
                               "QPushButton:pressed {"
                               "background-color: rgba(200, 5, 21, 1);"
                               "}");

}

void TeamsUI::initializeCancelButton()
{
    CancelButton = std::make_unique<QPushButton>();
    CancelButton->setText("Cancel");
    CancelButton->setFixedSize(246,32);
    CancelButton->setStyleSheet("QPushButton {"
                                "background-color: white;"
                                "color: #D72130;"
                                "border: 0px;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: rgba(248, 248, 248, 1);"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: white;"
                                "}");
}

void TeamsUI::initializeLocationLabel()
{
    LocationLabel = std::make_unique<QLabel>();
    LocationLabel->setText(QString("SELECT LOCATION"));
    LocationLabel->setFont(QFont("Roboto", -1, QFont::Bold));
    LocationLabel->setStyleSheet("QLabel { color : #7F8899; font-size: 10px; }");
}

void TeamsUI::initializeSubCategoryLabel()
{
    SubCategoryLabel = std::make_unique<QLabel>();
    SubCategoryLabel->setText(QString("SELECT SUBCATEGORY"));
    SubCategoryLabel->setFont(QFont("Roboto", -1, QFont::Bold));
    SubCategoryLabel->setStyleSheet("QLabel { color : #7F8899; font-size: 10px;}");
}

void TeamsUI::initializeTeamLabel()
{
    TeamLabel= std::make_unique<QLabel>();
    TeamLabel->setText(QString("TEAM"));
    TeamLabel->setFont(QFont("Roboto", -1, QFont::Bold));
    TeamLabel->setStyleSheet("QLabel { color : #7F8899; font-size: 10px;}");
}

void TeamsUI::initializeCategoryLabel()
{
    CategoryLabel = std::make_unique<QLabel>();
    CategoryLabel->setText(QString("SELECT CATEGORY"));
    CategoryLabel->setFont(QFont("Roboto", -1, QFont::Bold));
    CategoryLabel->setStyleSheet("QLabel { color : #7F8899; font-size: 10px;}");
}

void TeamsUI::initializeTeamImage()
{
    TeamImage = std::make_unique<QFrame>();
    TeamImage->setFixedSize(246, 155);
    TeamImage->setStyleSheet("QFrame { "
                             "background-color: white;"
                             "background-image: none;"
                             "border: 1px solid rgba(209, 209, 209, 1);"
                             "}"
                             "QFrame:hover { background-color: white; }");

    QVBoxLayout* layout = new QVBoxLayout(TeamImage.get());

    QWidget* container = new QWidget(TeamImage.get());
    layout->addWidget(container, 0, Qt::AlignCenter);

    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    //containerLayout->setSpacing(0); // Встановлення проміжку між елементами у контейнері

    CameraIcon = std::make_unique<QPushButton>(container);
    CameraIcon->setFixedSize(39, 39);
    QPixmap pixmap("../img/Camera.png");
    QIcon icon(pixmap);
    CameraIcon->setIcon(icon);
    CameraIcon->setIconSize(pixmap.size());
    CameraIcon->setFlat(true);
    CameraIcon->setAttribute(Qt::WA_TranslucentBackground);
    CameraIcon->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");

    containerLayout->addWidget(CameraIcon.get(), 0, Qt::AlignCenter);

    LogoText = std::make_unique<QLabel>(container);
    LogoText->setText("<span style='color: red; font-famile='Open Sans'>Add logo</span> <span style='color: black;'>right here</span>");
    LogoText->setAttribute(Qt::WA_TranslucentBackground);
    LogoText->setStyleSheet("font-family: 'Open Sans'; font-size: 14px;background-color: rgba(0, 0, 0, 0); border: none;");

    LogoText->setAlignment(Qt::AlignCenter);
    containerLayout->addWidget(LogoText.get(), 0, Qt::AlignCenter);

    connect(CameraIcon.get(), &QPushButton::clicked, this, &TeamsUI::openFileExplorer);



}

TeamsUI::TeamsUI()
{
    initializeLocationDrop();
    initializeCategoryDrop();
    initializeLocationLabel();
    initializeSubCategoryLabel();
    initializeCategoryLabel();
    initializeSubCategoryDrop();
    initializeTeamLabel();
    initializeTeamInput();
    initializeTeamImage();
    initializeApplyButton();
    initializeCancelButton();

    Layout = std::make_unique<QVBoxLayout>(this);



    Layout->addWidget(LocationLabel.get());
    Layout->addWidget(LocationDrop.get());

    Layout->addWidget(CategoryLabel.get());
    Layout->addWidget(CategoryDrop.get());

    Layout->addWidget(SubCategoryLabel.get());
    Layout->addWidget(SubCategoryDrop.get());

    Layout->addWidget(TeamLabel.get());
    Layout->addWidget(TeamInput.get());

    Layout->addWidget(TeamImage.get());

    Layout->addWidget(ApplyButton.get());
    Layout->addWidget(CancelButton.get());

    setStyleSheet("background-color: rgba(255, 255, 255, 1);");

    setLayout(Layout.get());


}


void TeamsUI::openFileExplorer()
{
    ImagePath = QFileDialog::getOpenFileName(this, "Відкрити файл", "", "Зображення (*.png *.jpg *.jpeg *.svg)");
    if (!ImagePath.isEmpty()) {

        QPixmap pixmap(ImagePath);
        QSize imageSize = TeamImage->size();
        pixmap = pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        TeamImage->setStyleSheet(QString("QFrame { border: none; background-image: url(%1); background-repeat: no-repeat; background-position: center; background-origin: content; background-clip: content; }QFrame:hover { background-color: white;background-image: none; }").arg(ImagePath));

        TeamIcon = QIcon(pixmap);


        isImageSet = true; // Встановити прапорець, що зображення встановлено

        // Приховати кнопки та текст, оскільки зображення встановлено
        CameraIcon->setVisible(false);
        LogoText->setVisible(false);
    }
}

void TeamsUI::enterEvent(QEnterEvent* event)
{
    if (event->type() == QEvent::Enter && isImageSet) {
        TeamImage->setStyleSheet("background-color: rgba(196, 196, 196, 0.08);");
        CameraIcon->setVisible(true);
        LogoText->setVisible(true);
   }

   QWidget::enterEvent(event);
}

void TeamsUI::leaveEvent(QEvent* event)
{
    if (event->type() == QEvent::Leave && isImageSet) {

        TeamImage->setStyleSheet(QString("QFrame { border: none; background-image: url(%1); background-repeat: no-repeat; background-position: center; background-origin: content; background-clip: content;}").arg(ImagePath));
        CameraIcon->setVisible(false);
        LogoText->setVisible(false);
    }

    QWidget::leaveEvent(event);
}

std::map<int,std::string> TeamsUI::GetLocations()
{

    std::string path = "http://localhost:8080"+Constants::locationsGet;

    HTTPRequestManager manager;
    auto a = manager.sendHTTPGetRequest(path);
    std::cout<<a<<std::endl;

    std::map<int, std::string> locationMap;


    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromStdString(a).toUtf8());


    if (jsonDocument.isNull())
    {
        std::cout << "Error parsing JSON response" << std::endl;
        return locationMap; // Повернути порожню map в разі помилки
    }


    if (jsonDocument.isObject())
    {
        QJsonObject jsonObject = jsonDocument.object();


        for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it)
        {
            int key = it.key().toInt();
            std::string value = it.value().toString().toStdString();
            locationMap[key] = value;
        }
    }
    return locationMap;
}

std::map<int, std::string> TeamsUI::GetCategories()
{
    std::map<int , std::string>categoriesMap;
    std::string All= "All";
    categoriesMap.insert(std::make_pair(0, All));

    auto future = std::async(std::launch::async, [](){
        return Client::getInstance().GetCategories();
    });

    const auto& categories = future.get();
    for (const auto& category : categories)
    {
        categoriesMap.insert(std::make_pair(category.getId(), category.getName()));
    }
    return categoriesMap;
}
