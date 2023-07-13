#ifndef CUSTOMCONTEXTMENU_H
#define CUSTOMCONTEXTMENU_H

#include <QMenu>
#include <QAction>

class CustomContextMenu : public QMenu
{
    Q_OBJECT

public:
    explicit CustomContextMenu(QWidget *parent = nullptr);

signals:
    void contextMenuRequested(const QPoint &pos);

public slots:
    void handleContextMenuRequested(const QPoint &pos);

private slots:
    void handleContextMenuAction();
};

#endif // CUSTOMCONTEXTMENU_H
