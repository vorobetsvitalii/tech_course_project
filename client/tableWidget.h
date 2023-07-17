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

// Custom delegate class for adding left padding to table cells
class TableCellDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        QStyleOptionViewItem modifiedOption = option;
        modifiedOption.rect.adjust(10, 0, 0, 0);  // Add 15px left padding to the cell rectangle
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

    const int columnNumber = 7;
    int width;
};


QString FindLocationById(int id);
QString FindSubcategoryById(int id, int* categoryId);
QString FindCategoryById(int id);

#endif // TABLEWIDGET_H
