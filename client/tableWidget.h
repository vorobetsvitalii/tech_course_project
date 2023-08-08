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

#include "paginationwidget.h"

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

    void initPagination();
    PaginationWidget* getPagination();

private:
    void fillWithData(std::vector<Team> &teams_data);
    void resizeTable();
    bool viewportEvent(QEvent* event);
    void showEvent(QShowEvent* event);
    void initializeCells();

    const int columnNumber = 7;
    int width;

    std::vector<Team> teams;
    std::vector<Team> filteredTeams;

    std::vector<QIcon> deleteIcons;
    bool isRowHovered;
    int hoveredRow = -1;
    std::vector<QStackedWidget*> rowStackedWidgets;

    std::unique_ptr<PaginationWidget> pagination;

    void setupRowWidgets(int row);
    void updateRowWidgetsVisibility(int row);
    
    void setPageResults(std::vector<Team> &teams_data);
    void refreshPageResults(std::vector<Team> &teams_data);

    const QString headerStyle = "QHeaderView::section {"
                                "    background-color: #EAEAEA;"
                                "    border: none;              "
                                "    alignment: AlignLeft;"
                                "    padding-left: 10px;"
                                "}";
    const QString rowStyle = "QTableWidget::item {"
                             "    background-color: #F2F2F2;"
                             "    color: black;"
                             "}";

public slots:
    void editButtonClicked(int row);
    void deleteButtonClicked(int row);
    void filterTeams(QString name, int locationId, int categoryId, int subcategoryId);
    void searchTeamByName(const QString& name);

    void onResultCountChanged();
    void onPageChanged();

};


QString FindLocationById(int id);
QString FindSubcategoryById(int id, int* categoryId);
QString FindCategoryById(int id);
int FindCategoryIdBySubcategoryId(int id);

#endif // TABLEWIDGET_H
