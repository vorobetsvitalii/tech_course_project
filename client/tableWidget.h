#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDebug>
#include <QStyledItemDelegate>

#include "../common/model/team.h"
#include "client.h"
#include "teamsui.h"

#include "deletepopup.h"
#include "editpopup.h"

#include <QVector>
#include <QIcon>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QPainterPath>

class TableCellDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QStyleOptionViewItem modifiedOption = option;
        modifiedOption.rect.adjust(10, 0, 0, 0);
        QStyledItemDelegate::paint(painter, modifiedOption, index);
    }
};

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget* parent = nullptr);

    void resize();

private:
    void fillWithData();
    void resizeTable();
     bool viewportEvent(QEvent* event);

    const int columnNumber = 7;
    int width;

    std::vector<QIcon> deleteIcons;
    bool isRowHovered;
    int hoveredRow = -1;
    std::vector<QStackedWidget*> rowStackedWidgets;

    void setupRowWidgets(int row);
    void updateRowWidgetsVisibility(int row);

public slots:
    void editButtonClicked(int row);
    void deleteButtonClicked(int row);


};


QString FindLocationById(int id);
QString FindSubcategoryById(int id, int* categoryId);
QString FindCategoryById(int id);

#endif // TABLEWIDGET_H
