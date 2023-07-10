#include "hmenu.h"
#include "hmenuitem.h"
#include "client.h"
#include <algorithm>
#include <QResizeEvent>

HMenu::HMenu()
{
    layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    leftArrowIcon = std::unique_ptr<QIcon>(new QIcon("../img/left-arrow.svg"));
    leftArrowIconActive = std::unique_ptr<QIcon>(new QIcon("../img/left-arrow-active.svg"));

    leftArrow = new QPushButton(*leftArrowIcon, "", this);
    leftArrow->setStyleSheet("padding: 15px; border: none;");
    leftArrow->setCursor(Qt::PointingHandCursor);
    leftArrow->setMaximumWidth(leftArrow->width());
    connect(leftArrow, &QPushButton::clicked, this, &HMenu::onLeftArrowClicked);
    connect(leftArrow, &QPushButton::clicked, this, &HMenu::changeArrowsView);

    rightArrowIcon = std::unique_ptr<QIcon>(new QIcon("../img/right-arrow.svg"));
    rightArrowIconActive = std::unique_ptr<QIcon>(new QIcon("../img/right-arrow-active.svg"));

    rightArrow = new QPushButton(*rightArrowIcon, "", this);
    rightArrow->setStyleSheet("padding: 15px; border: none;");
    rightArrow->setCursor(Qt::PointingHandCursor);
    rightArrow->setMaximumWidth(rightArrow->width());
    connect(rightArrow, &QPushButton::clicked, this, &HMenu::onRightArrowClicked);
    connect(rightArrow, &QPushButton::clicked, this, &HMenu::changeArrowsView);

    categories = Client::getInstance().GetCategories();
    clayout = new QHBoxLayout();

    for(auto& item : categories) {
        isVisible[item.getName()] = true;
        HMenuItem* menuItem = createHMenuItem(&item);
        items[item.getName()] = menuItem;
        clayout->addWidget(menuItem);
        connect(menuItem, &HMenuItem::itemSelected, this, &HMenu::onHMenuItemSelected);
    }

    itemsCount = categories.size();
    currentItem = nullptr;
    f_index = 0;

    layout->addWidget(leftArrow);
    layout->addLayout(clayout);
    layout->addWidget(rightArrow);

    this->setLayout(layout);
    this->setStyleSheet("border: none;");

}

HMenuItem* HMenu::createHMenuItem(Category* category)
{
    return new HMenuItem(category);
}

void HMenu::addCategory(Category* category) {
    categories.push_back(*category);
    isVisible[category->getName()] = true;
    HMenuItem* menuItem = createHMenuItem(category);
    items[category->getName()] = menuItem;
    clayout->addWidget(menuItem);
    connect(menuItem, &HMenuItem::itemSelected, this, &HMenu::onHMenuItemSelected);
}

void HMenu::hideCategory(Category* category)
{
    isVisible[category->getName()] = false;
    items[category->getName()]->hide();
}

void HMenu::showCategory(Category* category)
{
    isVisible[category->getName()] = true;
    items[category->getName()]->show();
}

void HMenu::setHidden(Category *category, bool isHidden)
{
    items[category->getName()]->setHidden(isHidden);
}

Category* HMenu::getCurrentCategory()
{
    return currentItem->getCategory();
}

void HMenu::resetCurrentCategory() {
    if(currentItem != nullptr)
        currentItem->setStyleSheet(currentItem->styleSheet().replace("color: #D72130;", "color: #B2B2B2;"));
    currentItem = nullptr;
}

void HMenu::changeArrowsView() {
    if(f_index != 0)
        leftArrow->setIcon(*leftArrowIconActive);
    else
        leftArrow->setIcon(*leftArrowIcon);

    if(f_index + itemsCount < categories.size())
        rightArrow->setIcon(*rightArrowIconActive);
    else
        rightArrow->setIcon(*rightArrowIcon);
}

void HMenu::onRightArrowClicked()
{
    if(f_index + itemsCount + 1 > categories.size()) return;
    showCategory(&categories[f_index+itemsCount]);
    hideCategory(&categories[f_index++]);
}

void HMenu::onLeftArrowClicked()
{
    if(f_index - 1 < 0) return;
    hideCategory(&categories[f_index+itemsCount-1]);
    showCategory(&categories[--f_index]);
}

void HMenu::onHMenuItemSelected(HMenuItem *item)
{
    if(currentItem != item) {
        if(currentItem != nullptr)
            currentItem->setStyleSheet(currentItem->styleSheet().replace("color: #D72130;", "color: #B2B2B2;"));
        currentItem = item;
        currentItem->setStyleSheet(currentItem->styleSheet().replace("color: #7F7B7B;", "color: #D72130;"));
    }

    emit categorySelected(currentItem->getCategory());
}

void HMenu::resizeEvent(QResizeEvent* event)
{
    int contentWidth = itemsCount*100 + leftArrow->width() + rightArrow->width();
    int diff = abs(event->size().width() - contentWidth);
    if(contentWidth < event->size().width())
    {
        for(int i = 0; i < diff / 100; i++)
            if(f_index + itemsCount < categories.size())
                showCategory(&categories[f_index + itemsCount++]);
            else if(f_index > 0)
            {
                showCategory(&categories[--f_index]);
                itemsCount++;
            }
            else break;
    }
    else
    {
        for(int i = 0; i < diff / 100; i++)
            if(itemsCount > 1)
                hideCategory(&categories[f_index + --itemsCount]);
            else break;
    }
    changeArrowsView();
}

