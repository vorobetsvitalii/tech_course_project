#ifndef HMENU_H
#define HMENU_H

#include <vector>
#include <memory>
#include <map>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include "../common/model/category.h"
#include "hmenuitem.h"

class HMenu: public QFrame
{
    Q_OBJECT

public:
    HMenu();

    void addCategory(Category* category);
    void setHidden(Category* category);
    Category* getCurrentCategory();
    void resetCurrentCategory();

private:
    std::map<std::string, HMenuItem*> items;
    std::vector<Category> categories;
    std::map<std::string, bool> isVisible;
    int itemsCount, f_index;

    HMenuItem* currentItem;

    QHBoxLayout* layout, *clayout;
    QPushButton* leftArrow, *rightArrow;
    std::unique_ptr<QIcon> leftArrowIcon, leftArrowIconActive, rightArrowIcon, rightArrowIconActive;

    HMenuItem* createHMenuItem(Category* category);
    void hideCategory(Category* category);
    void showCategory(Category* category);

private slots:
    void onRightArrowClicked();
    void onLeftArrowClicked();
    void changeArrowsView();
    void onHMenuItemSelected(HMenuItem* item);

signals:
    void categorySelected(Category* category);


protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // HMENU_H
