#include "tablewidget.h"


TableWidget::TableWidget(QWidget* parent) : QTableWidget(parent)
{
    setColumnCount(columnNumber);
    width = 730;
    resizeTable();
    setShowGrid(false);

    verticalHeader()->setVisible(false);
    QStringList headerLabels = {"Teams", "Location", "Added at", "Category", "Subcategory", "", ""};
    setHorizontalHeaderLabels(headerLabels);

    fillWithData();

    QHeaderView* header = horizontalHeader();
    header->setStyleSheet("QHeaderView::section {"
                          "    background-color: #EAEAEA;"
                          "    border: none;              "
                          "    alignment: AlignLeft;"
                          "    padding-left: 10px;"
                          "}");

    setSelectionBehavior(QAbstractItemView::SelectRows); // Виділення по рядках
    setEditTriggers(QAbstractItemView::NoEditTriggers); // Вимикаємо можливість редагування

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    TableCellDelegate* delegate = new TableCellDelegate();
    setItemDelegate(delegate);

    QString rowStyle = "QTableWidget::item {"
                       "    background-color: #F2F2F2;"
                       "}";
    setStyleSheet(rowStyle);

    for (int col = 0; col < columnNumber; ++col) {
        QTableWidgetItem* headerItem = horizontalHeaderItem(col);
        if (headerItem) {
            headerItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

}

void TableWidget::resize()
{
    width = parentWidget()->width();
    resizeTable();
}

void TableWidget::fillWithData()
{
    std::vector<team> teams = Client::getInstance().GetTeams();
    setRowCount(teams.size());

    for (int row = 0; row < rowCount(); ++row) {
        for (int col = 0; col < columnNumber - 2; ++col) {
            QTableWidgetItem* tableItem = item(row, col);
            if (tableItem) {
                tableItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            }
        }
    }

    // Додати дані до таблиці
    for (int i = 0; i < teams.size(); ++i)
    {
        qDebug() << teams[i].getTeamName() +" "+QString::number(teams[i].getTeamLocation())+" "+teams[i].getDate()+" "+QString::number(teams[i].getSubcategoryId())+" "+QString::number(teams[i].getSubcategoryId())+" ";

        int locationId = teams[i].getTeamLocation();
        int subcategoryId = teams[i].getSubcategoryId();
        int categoryId;
        QString locationName = FindLocationById(locationId);
        QString subcategoryName = FindSubcategoryById(subcategoryId, &categoryId);
        QString categoryName = FindCategoryById(categoryId);

        setItem(i, 0, new QTableWidgetItem(teams[i].getTeamName()));
        setItem(i, 1, new QTableWidgetItem(locationName));
        setItem(i, 2, new QTableWidgetItem(teams[i].getDate().left(10)));
        setItem(i, 3, new QTableWidgetItem(categoryName));
        setItem(i, 4, new QTableWidgetItem(subcategoryName));
    }
}

void TableWidget::resizeTable()
{
    int desireWidth = width - 10;
    setFixedWidth(desireWidth);
    double columnRatios[] = {0.2, 0.2, 0.15, 0.15, 0.15, 0.075, 0.075};

    for (int i = 0; i < columnNumber; i++) {
        int columnWidth = columnRatios[i] * desireWidth;
        setColumnWidth(i, columnWidth);
    }
}

QString FindLocationById(int id) {
    QString locationName;
    if (TeamsUI::LocationMap.find(id) != TeamsUI::LocationMap.end())
    {
        locationName = QString::fromStdString(TeamsUI::LocationMap[id]);
    }
    return locationName;
}

QString FindSubcategoryById(int id, int* categoryId) {
    QString subcategoryName;
    for (const auto& subCategory : TeamsUI::SubCategoriesAll) {
        if (subCategory.getId() == id) {
            *categoryId = subCategory.getCategoryId();
            subcategoryName = QString::fromStdString(subCategory.getName());
            break;
        }
    }
    return subcategoryName;
}

QString FindCategoryById(int id) {
    QString categoryName;
    if (TeamsUI::CategoriesMap.find(id) != TeamsUI::CategoriesMap.end())
    {
        categoryName = QString::fromStdString(TeamsUI::CategoriesMap[id]);
    }
    return categoryName;
}

