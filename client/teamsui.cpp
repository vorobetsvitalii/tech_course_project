#include "teamsui.h"

std::map<int,std::string> TeamsUI::LocationMap;
std::map<int,std::string> TeamsUI::CategoriesMap;
std::vector<Subcategory> TeamsUI::SubCategoriesAll;

QString TeamsUI::comboBoxStyle = "QComboBox {"
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


QString TeamsUI::listViewStyle="QListView::item {"
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
                                 "}";




void TeamsUI::initializeLocationDrop()
{
    LocationMap = GetLocations();
    LocationDrop = std::make_unique<QComboBox>();

    LocationDrop->setFixedSize(246,36);

    LocationDrop->setStyleSheet(comboBoxStyle);
    QListView * listView = new QListView();
    listView->setStyleSheet(listViewStyle);

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



    CategoryDrop->setStyleSheet(comboBoxStyle);
    QListView * listView = new QListView();
    listView->setStyleSheet(listViewStyle);

    //listView->setFixedSize(250,36);

    CategoryDrop->setView(listView);
    CategoryDrop->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    CategoryDrop->view()->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    CategoryDrop->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    CategoryDrop->view()->style()->setProperty("hoverHighlight", false);

    connect(CategoryDrop.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TeamsUI::onCategoryActivated);


    for (const auto& tmp : this->CategoriesMap) {
        CategoryDrop->addItem(QString::fromStdString(tmp.second));
    }
}


void TeamsUI::onCategoryActivated(int index)
{
    QString category = CategoryDrop->itemText(index);
    qDebug()<< category;


    auto SubCount = SubCategoriesVector.size();

    this->SubCategoriesVector.clear();

    for (auto tmp : SubCategoriesAll)
    {
       // qDebug() << QString::number(tmp.getCategoryId()) + "   " + QString::fromStdString(this->CategoriesMap[tmp.getCategoryId()]);
        if (this->CategoriesMap[tmp.getCategoryId()].compare(category.toStdString()) == 0)
        {
            this->SubCategoriesVector.push_back(tmp);
            //qDebug() <<QString("PUSH BACK\n");
        }

    }

    for (int i = 0; i < SubCount; i++) {
        SubCategoryDrop->removeItem(0);
    }
    //qDebug() << QString("SubCategoriesVector:");
    //for (const auto& tmp : SubCategoriesVector) {
    //    qDebug() << QString::fromStdString(tmp.getName());
    //}



    for (const auto& tmp : this->SubCategoriesVector) {
        SubCategoryDrop->addItem(QString::fromStdString(tmp.getName()));
    }

}

void TeamsUI::initializeSubCategoryDrop()
{
    SubCategoriesAll = GetSubCategories();

    SubCategoryDrop = std::make_unique<QComboBox>();


    SubCategoryDrop->setFixedSize(246,36);


    SubCategoryDrop->setStyleSheet(comboBoxStyle);
    QListView * listView = new QListView();
    listView->setStyleSheet(listViewStyle);

    //listView->setFixedSize(250,36);

    SubCategoryDrop->setView(listView);
    SubCategoryDrop->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    SubCategoryDrop->view()->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    SubCategoryDrop->setCursor(QCursor(QPixmap("../img/Cursor.png")));
    SubCategoryDrop->view()->style()->setProperty("hoverHighlight", false);

    for (const auto& tmp : this->SubCategoriesVector) {
        SubCategoryDrop->addItem(QString::fromStdString(tmp.getName()));
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
    ApplyButton.reset(new QPushButton());
    ApplyButton->setText("Apply");
    ApplyButton->setFixedSize(246, 32);
    ApplyButton->setStyleSheet("QPushButton {"
                               "background-color: rgba(224, 34, 50, 1);"
                               "color: white;"
                               "border: 0px;"
                               "}"
                               "QPushButton:pressed {"
                               "background-color: rgba(200, 5, 21, 1);"
                               "}");

    connect(ApplyButton.data(), &QPushButton::clicked, this, &TeamsUI::CreateTeam);
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
    connect(CancelButton.get(), &QPushButton::clicked, this, &TeamsUI::Cancel);
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

void TeamsUI::ApplyButtonCheck()
{
    /*try{
    QString CategoryText = this->CategoryDrop->currentText();
    QString SubCategoryText = this->SubCategoryDrop->currentText();
    QString LocationText = this->LocationDrop->currentText();
    QString TeamName = this->TeamInput->text();
    QString Image = this->ImagePath;

    if(!CategoryText.isNull() && !SubCategoryText.isNull() && !LocationText.isEmpty() && !TeamName.isNull() && !Image.isNull()){
            this->ApplyButton->setStyleSheet("QPushButton {"
                                         "background-color: rgba(247, 211, 214, 1);"
                                         "color: white;"
                                         "border: 0px;"
                                         "}");
    }
    else{
        /his->ApplyButton->setStyleSheet("QPushButton {"
                                         "background-color: rgba(224, 34, 50, 1);"
                                         "color: white;"
                                         "border: 0px;"
                                         "}");
    }
    }catch(std::exception exp){qDebug()<<exp.what();}*/
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
        ApplyButtonCheck();
   }

   QWidget::enterEvent(event);
}

void TeamsUI::leaveEvent(QEvent* event)
{
    if (event->type() == QEvent::Leave && isImageSet) {

        TeamImage->setStyleSheet(QString("QFrame { border: none; background-image: url(%1); background-repeat: no-repeat; background-position: center; background-origin: content; background-clip: content;}").arg(ImagePath));
        CameraIcon->setVisible(false);
        LogoText->setVisible(false);
        ApplyButtonCheck();
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

std::vector<Subcategory> TeamsUI::GetSubCategories()
{


    auto future = std::async(std::launch::async, [](){
        return Client::getInstance().GetSubcategories();
    });

    const auto& subcategories = future.get();

    return subcategories;

}

void TeamsUI::CreateTeam()
{
    qDebug()<<"CreateTeam";
    team Team;
    QString CategoryText = this->CategoryDrop->currentText();
    QString SubCategoryText = this->SubCategoryDrop->currentText();
    QString LocationText = this->LocationDrop->currentText();
    QString TeamName = this->TeamInput->text();

    if(!CategoryText.isNull() && !SubCategoryText.isNull() && !LocationText.isEmpty() && !TeamName.isNull() && !this->ImagePath.isNull()){QMessageBox::information(nullptr, "Apply", "Конанду додано");}
    else{QMessageBox::information(nullptr, "Apply", "Конанду не додано"); return;}
    if(!SubCategoryText.isEmpty()){
    for(const auto tmp: this->SubCategoriesVector)
    {
        if(tmp.getName()==SubCategoryText.toStdString())
        {
            Team.setSubcategoryId(tmp.getId());
            break;
        }
    }}else{return;}

    if(!LocationText.isEmpty()){
    for (const auto pair : this->LocationMap) {
        if (pair.second == LocationText.toStdString()) {
            Team.setTeamLocation(pair.first);
            break;
        }
    }}else{return;}

    if(!TeamName.isEmpty()){
        Team.setTeamName(TeamName);
    }else{return;}

    if(!this->ImagePath.isEmpty())
    {
        Team.setTeamLogoBlob(this->ImagePath);

    }else{return;}
    qDebug()<<SubCategoryText+"  "+QString::number( Team.getSubcategoryId())+  " " +LocationText+"  "+QString::number(Team.getTeamLocation())+"  "+Team.getTeamName()+"   "+this->ImagePath;
    Client::getInstance().PostTeam(Team);
}

void TeamsUI::Cancel()
{
    qDebug()<<"Cancel";
}
