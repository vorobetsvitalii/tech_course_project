#include "menubutton.h"


std::shared_ptr<QPushButton> ButtonsForMenu::CSTButton = nullptr;
std::shared_ptr<QPushButton> ButtonsForMenu::TeamButton= nullptr;

TeamsUI* MenuButton::teamui = nullptr;
TeamUIFilter* MenuButton::teamfilter = nullptr;

MenuButton::MenuButton(const QString& name, const QString& tooltip, const QIcon& icon, QWidget* parent, AdminPage* adminpage)
    : QPushButton(parent), originalIcon(icon)
{
    button = this;

    this->adminpage = adminpage;
    //ButtonsForMenu::CSTButton = std::move(adminpage->saveChangesButton);


    button->setFlat(true);
    button->setToolTip(tooltip);
    button->setFixedSize(50,50);

    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet("QPushButton {"
                          "    text-align: center;"
                          "    padding: 0px;"
                          "    border: none;"
                          "    color: transparent;"
                          "}"
                          "QPushButton::focus { outline: none; }");
    installEventFilter(this);
    setButtonIcon(convertToGrayIcon(icon));

    buttonName = name;
}

bool MenuButton::eventFilter(QObject* object, QEvent* event)
{
    if (object == button) {
        if (event->type() == QEvent::Enter) {
            showTooltip();
            setButtonIcon(originalIcon);
        } else if (event->type() == QEvent::Leave) {
            hideTooltip();
            MenuButton* menuButton = dynamic_cast<MenuButton*>(object);
            if(!menuButton->clicked)
            {
                setButtonIcon(convertToGrayIcon(originalIcon));
            }
        }
    }
    return QPushButton::eventFilter(object, event);
}

void MenuButton::addTeamButtonClicked()
{
    teamfilter->setVisible(false);
    teamui->setVisible(true);
}

void MenuButton::showFilterForTeamTable()
{
    teamfilter->setVisible(true);
    teamui->setVisible(false);
}

void MenuButton::SetAdvertising(MenuButton *clickedButton, QScrollArea *Content)
{
    clickedButton->advertisingContent = clickedButton->initializeAdvertisingContent();
    Content->setWidget(clickedButton->advertisingContent.release());
}



void MenuButton::SetBanners(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->bannersContent = clickedButton->initializeBannersContent();
    Content->setWidget(clickedButton->bannersContent.release());
}


void MenuButton::SetNewsPartners(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->newsPartnersContent = clickedButton->initializeNewsPartnersContent();
    Content->setWidget(clickedButton->newsPartnersContent.release());
}


void MenuButton::SetSocialNetworks(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->socialNetworksContent = clickedButton->initializeSocialNetworksContent();
    Content->setWidget(clickedButton->socialNetworksContent.release());
}


void MenuButton::SetSurveys(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->surveysContent = clickedButton->initializeSurveysContent();
    Content->setWidget(clickedButton->surveysContent.release());
}


void MenuButton::SetFooter(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->footerContent = clickedButton->initializeFooterContent();
    Content->setWidget(clickedButton->footerContent.release());
}


void MenuButton::SetTeams(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->teamsContent = clickedButton->initializeTeamsContent();
    Content->setWidget(clickedButton->teamsContent.release());
}


void MenuButton::SetUsers(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->usersContent = clickedButton->initializeUsersContent();
    Content->setWidget(clickedButton->usersContent.release());
}


void MenuButton::SetLanguages(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->languagesContent = clickedButton->initializeLanguagesContent();
    Content->setWidget(clickedButton->languagesContent.release());
}


void MenuButton::SetIA(MenuButton* clickedButton ,QScrollArea* Content)
{
    clickedButton->iaContent = clickedButton->initializeIAContent();
    Content->setWidget(clickedButton->iaContent.release());
}

QIcon MenuButton::GetIcon()
{
    return this->originalIcon;
}

void MenuButton::setButtonIcon(const QIcon& icon)
{
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
}

void MenuButton::showTooltip()
{
    QPoint tooltipPos = button->mapToGlobal(button->rect().center());
    tooltipPos.setX(tooltipPos.x() + button->rect().width() / 2);
    tooltipPos.setY(tooltipPos.y() - button->rect().height() / 2);
    QToolTip::showText(tooltipPos, button->toolTip(), button);
}

void MenuButton::hideTooltip()
{
    QToolTip::hideText();
}

std::unique_ptr<QWidget> MenuButton::initializeAdvertisingContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("Advertising");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeBannersContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("Banners");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeNewsPartnersContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("News Partners");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeSocialNetworksContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("Social Networks");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeSurveysContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("Surveys");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeFooterContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("Footer");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeTeamsContent()
{
    std::unique_ptr<ResizableWidget> widget = std::make_unique<ResizableWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());

   // if(!teamui){
    teamui = new TeamsUI(false);
    teamfilter= new TeamUIFilter();
    //}
    TableWidget* tableWidget = new TableWidget();
    tableWidget->initPagination();


    SearchLine* searchLine = new SearchLine();
    PaginationWidget* pagination = tableWidget->getPagination();

    layout->addWidget(teamui);
    layout->addWidget(teamfilter);
    
    layout->addWidget(searchLine);

    layout->addWidget(tableWidget);
    layout->addWidget(pagination);

    widget->setLayout(layout);
    widget->setWindowTitle("Teams");

    QObject::connect(adminpage, &AdminPage::adminPageResized, widget.get(), &ResizableWidget::resize);
    QObject::connect(widget.get(), &ResizableWidget::resizableWidgetResized, tableWidget, &TableWidget::resize);
    QObject::connect(searchLine, &SearchLine::nameChanged, tableWidget, &TableWidget::searchTeamByName);

    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeUsersContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("Users");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeLanguagesContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QVBoxLayout* layout = new QVBoxLayout(widget.get());
    QLabel* label = new QLabel("Languages");
    layout->addWidget(label);
    widget->layout()->deleteLater();
    widget->setLayout(layout);
    return widget;
}

std::unique_ptr<QWidget> MenuButton::initializeIAContent()
{
    std::unique_ptr<QWidget> widget = std::make_unique<QWidget>();
    QHBoxLayout* IAContentLayout = new QHBoxLayout();

    widget->layout()->deleteLater();

    IAContentLayout->addLayout(categoriesVLayout);
    IAContentLayout->addSpacing(40);
    IAContentLayout->addLayout(subcategoriesVLayout);
    IAContentLayout->addSpacing(40);
    IAContentLayout->addLayout(teamsVLayout);
    IAContentLayout->addSpacing(40);

    widget->setLayout(IAContentLayout);

    return widget;
}

QIcon MenuButton::convertToGrayIcon(const QIcon& icon)
{
    QList<QSize> sizes = icon.availableSizes();
    QIcon grayIcon;
    for (const QSize& size : sizes) {
        QPixmap pixmap = icon.pixmap(size);
        QImage image = pixmap.toImage().convertToFormat(QImage::Format_ARGB32);
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QRgb pixel = image.pixel(x, y);
                int gray = qGray(pixel);
                image.setPixel(x, y, qRgba(gray, gray, gray, qAlpha(pixel)));
            }
        }
        grayIcon.addPixmap(QPixmap::fromImage(image));
    }
    return grayIcon;
}

void MenuButton::setCategoriesLayout(QVBoxLayout *categoriesVLayout_)
{
    categoriesVLayout = categoriesVLayout_;
}

void MenuButton::setSubcategoriesLayout(QVBoxLayout *subcategoriesVLayout_)
{
    subcategoriesVLayout = subcategoriesVLayout_;
}

void MenuButton::setTeamsLayout(QVBoxLayout *teamsVLayout_)
{
    teamsVLayout = teamsVLayout_;
}

QString MenuButton::GetItemName() {
    return buttonName;
}


void handleMenuItemClick(MenuButton* clickedButton ,QScrollArea* Content)
{
    QString buttonText = clickedButton->toolTip();
    qDebug() << "Button clicked: " << buttonText;
    std::map<std::string, int> Values;
    Values.emplace("Advertising", 1);
    Values.emplace("Banners", 2);
    Values.emplace("News Partners", 3);
    Values.emplace("Social Networks", 4);
    Values.emplace("Surveys", 5);
    Values.emplace("Footer", 6);
    Values.emplace("Teams", 7);
    Values.emplace("Users", 8);
    Values.emplace("Languages", 9);
    Values.emplace("IA", 10);



    QObjectList children = clickedButton->parentWidget()->children();
    for (QObject* child : children)
    {
        if (MenuButton* menuButton = qobject_cast<MenuButton*>(child))
        {
            if (menuButton != clickedButton && menuButton->clicked)
            {
                menuButton->clicked=false;
                menuButton->setIcon(menuButton->convertToGrayIcon(menuButton->GetIcon()));
            }
        }
    }


    clickedButton->clicked=true;
    QIcon originalIcon = clickedButton->GetIcon();

    // Змініть іконку натиснутої кнопки на оригінальну
    clickedButton->setButtonIcon(originalIcon);


    switch(Values[clickedButton->toolTip().toStdString()])
    {
    case 1:
    {
        clickedButton->SetAdvertising(clickedButton , Content);
        break;
    }
    case 2:
    {
        clickedButton->SetBanners(clickedButton , Content);
        break;
    }
    case 3:
    {
        clickedButton->SetNewsPartners(clickedButton , Content);
        break;
    }
    case 4:
    {
        clickedButton->SetSocialNetworks(clickedButton , Content);
        break;
    }
    case 5:
    {
        clickedButton->SetSurveys(clickedButton , Content);
        break;
    }
    case 6:
    {
        clickedButton->SetFooter(clickedButton , Content);
        break;
    }
    case 7:
    {
        clickedButton->SetTeams(clickedButton , Content);
        break;
    }
    case 8:
    {
        clickedButton->SetUsers(clickedButton , Content);
        break;
    }
    case 9:
    {
        clickedButton->SetLanguages(clickedButton , Content);
        break;
    }
    case 10:
    {
        clickedButton->SetIA(clickedButton , Content);
        break;
    }
    default: return ;break;
    }

}

QVBoxLayout* MenuButton::categoriesVLayout = nullptr;
QVBoxLayout* MenuButton::subcategoriesVLayout = nullptr;
QVBoxLayout* MenuButton::teamsVLayout = nullptr;

std::shared_ptr<QPushButton> ButtonsForMenu::TeamButtonInit()
{
    std::shared_ptr<QPushButton> button = std::make_shared<QPushButton>();
    button->setText("Add team");
    button->setFixedSize(110, 30);
    button->setStyleSheet("QPushButton { \
                        background-color: rgb(208, 0, 0); \
                        color: rgb(255, 255, 255); border:none}");

    return button;
}

