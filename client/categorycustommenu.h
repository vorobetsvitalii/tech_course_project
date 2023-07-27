#ifndef CATEGORYCUSTOMMENU_H
#define CATEGORYCUSTOMMENU_H

#include <QMenu>
#include <QAction>
#include <QPushButton>

#include "../common/model/subcategory.h"
#include "deletepopup.h"
#include "editpopup.h"

class CategoryCustomMenu : public QMenu
{
    Q_OBJECT

public:
    explicit CategoryCustomMenu(QWidget *parent = nullptr);

    static void setCategoryIndex(const int& index_);
    static void setTempCategoryButton(QPushButton* temp_category_button_);

    void onCategoryNameUpdated(const QString& newName);
private:
    static QPushButton* temp_category_button;

    std::vector<Category> categoriesList;

    QAction *action1;
    QAction *action2;
    QAction *action3;

    static int index;

signals:
    void contextMenuRequested(const QPoint &pos);

public slots:
    void handleContextMenuRequested(const QPoint &pos);

private slots:
    void handleContextMenuAction();
};

#endif // CATEGORYCUSTOMMENU_H
