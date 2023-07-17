#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDebug>

#include "../common/model/team.h"
#include "client.h"

#include <QStyledItemDelegate>

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

#endif // TABLEWIDGET_H
