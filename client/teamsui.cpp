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

        if (this->CategoriesMap[tmp.getCategoryId()].compare(category.toStdString()) == 0)
        {
            this->SubCategoriesVector.push_back(tmp);

        }

    }

    for (int i = 0; i < SubCount; i++) {
        SubCategoryDrop->removeItem(0);
    }




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
    ApplyButton->setText("Add Team");
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


}

TeamsUI::TeamsUI(const bool visible)
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

    this->setVisible(visible);
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


    std::string path = "http://"+Constants::IP+":"+Constants::Port+Constants::locationsGet;

    HTTPRequestManager manager;
    auto responce = manager.sendHTTPGetRequest(path);
    std::cout<<responce<<std::endl;

    std::map<int, std::string> locationMap;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString::fromStdString(responce).toUtf8());


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
    Team team;
    QString CategoryText = this->CategoryDrop->currentText();
    QString SubCategoryText = this->SubCategoryDrop->currentText();
    QString LocationText = this->LocationDrop->currentText();
    QString TeamName = this->TeamInput->text();

    if (!CategoryText.isNull() && !SubCategoryText.isNull() && !LocationText.isEmpty() && !TeamName.isNull() && !this->ImagePath.isNull()) {
        QMessageBox applyMessageBox;
        applyMessageBox.setText("Команду додано");
        applyMessageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        applyMessageBox.setStyleSheet(
            "QMessageBox {"
            "   background-color: rgba(248, 248, 248, 1);"
            "   font-size: 14px;"  // Розмір шрифту
            "}");
        ;
        applyMessageBox.exec();
    } else {
        QMessageBox applyMessageBox;
        applyMessageBox.setText("Команду не додано");
        applyMessageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        applyMessageBox.setStyleSheet(
            "QMessageBox {"
            "   background-color: rgba(248, 248, 248, 1);"
            "   font-size: 14px;"  // Розмір шрифту
            "}");
        ;
        applyMessageBox.exec();
        return;
    }

    if(!SubCategoryText.isEmpty()){
        for(const auto tmp: this->SubCategoriesVector)
        {
            if(tmp.getName()==SubCategoryText.toStdString())
            {
                team.setSubcategoryId(tmp.getId());
                break;
            }
        }}else{return;}

    if(!LocationText.isEmpty()){
        for (const auto pair : this->LocationMap) {
            if (pair.second == LocationText.toStdString()) {
                team.setTeamLocation(pair.first);
                break;
            }
        }}else{return;}

    if(!TeamName.isEmpty()){
        team.setTeamName(TeamName);
    }else{return;}

    if(!this->ImagePath.isEmpty())
    {
        team.setTeamLogoBlob(this->ImagePath);

    }else{return;}
    qDebug()<<SubCategoryText+"  "+QString::number( team.getSubcategoryId())+  " " +LocationText+"  "+QString::number(team.getTeamLocation())+"  "+team.getTeamName()+"   "+this->ImagePath;
    Client::getInstance().PostTeam(team);
}

void TeamsUI::Cancel()
{
    MenuButton::teamui->setVisible(false);
    MenuButton::teamfilter->setVisible(true);
    qDebug()<<"Cancel";
}



void TeamUIFilter::initializeApplyButton()
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
    connect(ApplyButton.get(), &QPushButton::clicked, this, &TeamUIFilter::applyButtonEvent);
}

void TeamUIFilter::initializeCancelButton()
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
    connect(CancelButton.get(), &QPushButton::clicked, this, &TeamUIFilter::Cancel);
    //this->setVisible(false);
}
void TeamUIFilter::Cancel()
{
    this->setVisible(false);
}
void TeamUIFilter::enterEvent(QEnterEvent *event)
{

}

void TeamUIFilter::leaveEvent(QEvent *event)
{

}

TeamUIFilter::TeamUIFilter()
{

    initializeLocationDrop();
    initializeCategoryDrop();
    initializeLocationLabel();
    initializeSubCategoryLabel();
    initializeCategoryLabel();
    initializeSubCategoryDrop();

    initializeApplyButton();
    initializeCancelButton();

    Frame = std::make_unique<QFrame>();
    Frame->setFixedSize(246, 155);

    Layout = std::make_unique<QVBoxLayout>(this);

    Layout->addWidget(LocationLabel.get());
    Layout->addWidget(LocationDrop.get());

    Layout->addWidget(CategoryLabel.get());
    Layout->addWidget(CategoryDrop.get());

    Layout->addWidget(SubCategoryLabel.get());
    Layout->addWidget(SubCategoryDrop.get());

    Layout->addWidget(Frame.get());


    Layout->addWidget(ApplyButton.get());
    Layout->addWidget(CancelButton.get());

    setStyleSheet("background-color: rgba(255, 255, 255, 1);");

    setLayout(Layout.get());
}

void TeamUIFilter::applyButtonEvent()
{
    Subcategory* currentSub = nullptr;
    int locationId = -1; // За замовчуванням, якщо не знайдено
    if(CategoryDrop->currentText()!="All"){
        std::string currentText = SubCategoryDrop->currentText().toStdString();
        auto it = std::find_if(SubCategoriesVector.begin(), SubCategoriesVector.end(), [&currentText](const Subcategory& subCategory) {
            return subCategory.getName() == currentText;
        });



        if (it != SubCategoriesVector.end()) {

            currentSub = &(*it);
        }

    }else{currentSub = new Subcategory();
        currentSub->setId(0);currentSub->setCategoryId(0);
    }
    QString selectedLocation = LocationDrop->currentText();

    if(selectedLocation != "All"){
        for (const auto& entry : LocationMap) {
            if (entry.second == selectedLocation.toStdString()) {
                locationId = entry.first;
                break;
            }
        }
    }else{locationId =0;}
    qDebug()<< QString::number(locationId) +QString::number(currentSub->getCategoryId())+QString::number(currentSub->getId()) ;
    emit teamsFilterRequested("",locationId ,currentSub->getCategoryId() ,currentSub->getId() );
    delete currentSub;
}
Team TeamsEditUI::selectedTeam = Team();
TeamsEditUI::TeamsEditUI(const Team& SelectedTeam)
{
    selectedTeam = SelectedTeam;
    initializeLocationDrop();
    initializeCategoryDrop();
    initializeLocationLabel();
    initializeSubCategoryLabel();
    initializeCategoryLabel();
    initializeSubCategoryDrop();
    initializeTeamLabel();
    initializeTeamInput();
    initializeTeamsImage();
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

    Layout->addWidget(imageLabel.get());

    Layout->addWidget(ApplyButton.get());
    Layout->addWidget(CancelButton.get());

    setStyleSheet("background-color: rgba(255, 255, 255, 1);");

    setLayout(Layout.get());

}
void TeamsEditUI::initializeTeamsImage()
{
    imageLabel = std::make_unique<QLabel>();
    imageLabel->setFixedSize(246, 155);
    imageLabel->setStyleSheet("QLabel { "
                              "background-color: white;"
                              "background-image: none;"
                              "border: 1px solid rgba(209, 209, 209, 1);"
                              "}"
                              "QLabel:hover { background-color: white; }");

    QVBoxLayout* layout = new QVBoxLayout(imageLabel.get());

    QWidget* container = new QWidget(imageLabel.get());
    layout->addWidget(container, 0, Qt::AlignCenter);

    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    //containerLayout->setSpacing(0); // Встановлення проміжку між елементами у контейнері

    ClickableButton = std::make_unique<QPushButton>(container);
    ClickableButton->setFixedSize(39, 39);
    ClickableButton->setFlat(true);
    ClickableButton->setAttribute(Qt::WA_TranslucentBackground);
    ClickableButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");

    containerLayout->addWidget(ClickableButton.get(), 0, Qt::AlignCenter);

    connect(ClickableButton.get(), &QPushButton::clicked, this, &TeamsEditUI::openFilesExplorer);

}
void TeamsEditUI::openFilesExplorer()
{
    ImagePath = QFileDialog::getOpenFileName(this, "Відкрити файл", "", "Зображення (*.png *.jpg *.jpeg *.svg)");
    if (!ImagePath.isEmpty()) {

        QPixmap pixmap(ImagePath);
        QSize imageSize = imageLabel->size();
        pixmap = pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        imageLabel->clear();
        imageLabel->setStyleSheet(QString("QLabel { border: none; background-image: url(%1); background-repeat: no-repeat; background-position: center; background-origin: content; background-clip: content; }QLabel:hover { background-color: white;background-image: none; }").arg(ImagePath));

        TeamIcon = QIcon(pixmap);


        //isImageSet = true; // Встановити прапорець, що зображення встановлено
        ClickableButton->setVisible(false);

        imageLabel->setVisible(true);
    }

}
Team TeamsEditUI::getSelectedTeam()
{
    LocationDrop->setCurrentText(FindLocationById(selectedTeam.getTeamLocation()));
    CategoryDrop->setCurrentText(FindCategoryById(FindCategoryIdBySubcategoryId(selectedTeam.getSubcategoryId())));
    int categoryId = FindCategoryIdBySubcategoryId(selectedTeam.getSubcategoryId());
    SubCategoryDrop->setCurrentText(FindSubcategoryById(selectedTeam.getSubcategoryId(), &categoryId));
    TeamInput->setText(selectedTeam.getTeamName());

    if (!selectedTeam.getTeamLogoBlob().isEmpty()) {
        QByteArray imageData = QByteArray::fromBase64(selectedTeam.getTeamLogoBlob().toLatin1());
        QImage teamImage;
        teamImage.loadFromData(imageData);

        QPixmap teamPixmap = QPixmap::fromImage(teamImage);
        if (!teamPixmap.isNull()) {

            QSize imageSize = imageLabel->size();
            teamPixmap = teamPixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            // imageLabel = std::make_unique<QLabel>();
            // imageLabel->setFixedSize(246, 155);
            imageLabel->setPixmap(teamPixmap);
            imageLabel->setScaledContents(true);
            //TeamImage->layout()->addWidget(imageLabel.get());
        }
    }
    /* if (!selectedTeam.getTeamLogoBlob().isEmpty()) {
        QByteArray imageData = QByteArray::fromBase64(selectedTeam.getTeamLogoBlob().toLatin1());

        QImage teamImage;
        teamImage.loadFromData(imageData);

    if (!teamImage.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(teamImage);
        QSize imageSize = TeamImage->size();
        pixmap = pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        TeamImage->setStyleSheet(QString("QFrame { border: none; background-image: url(%1); background-repeat: no-repeat; background-position: center; background-origin: content; background-clip: content; }QFrame:hover { background-color: white;background-image: none; }").arg(ImagePath));

        TeamIcon = QIcon(pixmap);

        // Hide the CameraIcon and LogoText
        CameraIcon->setVisible(false);
        LogoText->setVisible(false);
    }
   }*/
    return selectedTeam;
}
TeamsEditUI::TeamsEditUI()
{

}
std::map<int, std::string> TeamsEditUI::GetSubcategories()
{
    std::map<int, std::string> subcategoriesMap;
    std::string All = "All";
    subcategoriesMap.insert(std::make_pair(0, All));

    auto future = std::async(std::launch::async, []() {
        return Client::getInstance().GetSubcategories();
    });

    const auto& subcategories = future.get();
    for (const auto& subcategory : subcategories)
    {
        subcategoriesMap.insert(std::make_pair(subcategory.getId(), subcategory.getName()));
    }
    return subcategoriesMap;
}

void TeamsEditUI::initializeApplyButton()
{
    ApplyButton.reset(new QPushButton());
    ApplyButton->setText("Save");
    ApplyButton->setFixedSize(246, 32);
    ApplyButton->setStyleSheet("QPushButton {"
                               "background-color: rgba(224, 34, 50, 1);"
                               "color: white;"
                               "border: 0px;"
                               "}"
                               "QPushButton:pressed {"
                               "background-color: rgba(200, 5, 21, 1);"
                               "}");

    connect(ApplyButton.data(), &QPushButton::clicked, this, &TeamsEditUI::EditTeam);
}
void TeamsEditUI::initializeCancelButton()
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
    connect(CancelButton.get(), &QPushButton::clicked, this, &TeamsEditUI::CancelEdit);
}
void TeamsEditUI::EditTeam()
{
    qDebug()<<"EditTeam";
    QString CategoryName = this->CategoryDrop->currentText();
    QString SubCategoryName = this->SubCategoryDrop->currentText();
    QString LocationName = this->LocationDrop->currentText();
    QString TeamName = this->TeamInput->text();

    std::map<int, std::string> locationMap = GetLocations();

    int locationId = 0;
    for (const auto& [id, name] : locationMap)
    {
        if (name == LocationName.toStdString())
        {
            locationId = id;
            break;
        }
    }
    std::map<int, std::string> subcategoryMap = GetSubcategories();

    int subcategoryId=0;

    for (const auto& [id, name] : subcategoryMap)
    {
        if (name == SubCategoryName.toStdString())
        {
            subcategoryId = id;
            break;
        }
    }
    if (locationId!=0&&subcategoryId!=0){
        selectedTeam.setSubcategoryId(subcategoryId);
        selectedTeam.setTeamLocation(locationId);
        selectedTeam.setTeamName(TeamName);
        if(!this->ImagePath.isEmpty())
        {
            selectedTeam.setTeamLogoBlob(this->ImagePath);

        }else{return;}
    }
    Client::getInstance().EditTeam(selectedTeam);
    qDebug()<<SubCategoryName+"  "+QString::number( selectedTeam.getSubcategoryId())+  " " +LocationName+"  "+QString::number(selectedTeam.getTeamLocation())+"  "+selectedTeam.getTeamName()+"   "+this->ImagePath;
    emit TeamEdited(getSelectedTeam());
    //close();
    setVisible(false);
}
void TeamsEditUI::CancelEdit()
{
    setVisible(false);
        //close();
}
