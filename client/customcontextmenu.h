#ifndef CUSTOMCONTEXTMENU_H
#define CUSTOMCONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include "addcategory.h"
#include "client.h"

class CustomContextMenu : public QMenu
{
    Q_OBJECT

public:
    explicit CustomContextMenu(QWidget *parent = nullptr);

    static void setSubcategoryIndex(const int& index_);

private:
    AddCategory* addCategoryWindow;

    static int index;

signals:
    void contextMenuRequested(const QPoint &pos);

public slots:
    void handleContextMenuRequested(const QPoint &pos);

private slots:
    void handleContextMenuAction();
};

#endif // CUSTOMCONTEXTMENU_H
