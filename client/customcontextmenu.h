#ifndef CUSTOMCONTEXTMENU_H
#define CUSTOMCONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include <QPushButton>

class CustomContextMenu : public QMenu
{
    Q_OBJECT

public:
    explicit CustomContextMenu(QWidget *parent = nullptr);

    static void setSubcategoryIndex(const int& index_);
    static void setTempSubcategoryButton(QPushButton* temp_subcategory_button_);
private:
    static QPushButton* temp_subcategory_button;

    static int index;

signals:
    void contextMenuRequested(const QPoint &pos);

public slots:
    void handleContextMenuRequested(const QPoint &pos);

private slots:
    void handleContextMenuAction();
};

#endif // CUSTOMCONTEXTMENU_H
