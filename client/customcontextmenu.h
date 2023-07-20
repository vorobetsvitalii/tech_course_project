#ifndef CUSTOMCONTEXTMENU_H
#define CUSTOMCONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include <QPushButton>

#include "../common/model/subcategory.h"
#include "deletepopup.h"
#include "editpopup.h"

class CustomContextMenu : public QMenu
{
    Q_OBJECT

public:
    explicit CustomContextMenu(QWidget *parent = nullptr);

    static void setSubcategoryIndex(const int& index_);
    static void setTempSubcategoryButton(QPushButton* temp_subcategory_button_);

    void onSubcategoryNameUpdated(const QString& newName);
private:
    static QPushButton* temp_subcategory_button;

    std::vector<Subcategory> subcategoriesList;

    static int index;

signals:
    void contextMenuRequested(const QPoint &pos);

public slots:
    void handleContextMenuRequested(const QPoint &pos);

private slots:
    void handleContextMenuAction();
};

#endif // CUSTOMCONTEXTMENU_H
