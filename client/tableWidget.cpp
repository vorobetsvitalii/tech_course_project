#include "tablewidget.h"


TableWidget::TableWidget(QWidget* parent) : QTableWidget(parent)
{
    // Встановлюємо кількість колонок та рядків
    setColumnCount(columnNumber);
    setRowCount(5);

    width = 700;
    resizeTable();
    // Вимикаємо відображення сітки
    setShowGrid(false);

    verticalHeader()->setVisible(false);
    // Встановлюємо назви стовпців
    QStringList headerLabels = {"Teams", "Location", "Added at", "Category", "Subcategory", "", ""};
    setHorizontalHeaderLabels(headerLabels);

    fillWithData();

    // Налаштовуємо вигляд заголовків
    QHeaderView* header = horizontalHeader();
    header->setStyleSheet("QHeaderView::section {"
                          "    background-color: #EAEAEA;"
                          "    border: none;              "
                          "    alignment: AlignLeft;"
                          "    padding-left: 10px;"
                          "}");

    // Додаткові налаштування для вигляду таблиці
    setSelectionBehavior(QAbstractItemView::SelectRows); // Виділення по рядках
    setEditTriggers(QAbstractItemView::NoEditTriggers); // Вимикаємо можливість редагування

    ///////////////

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    TableCellDelegate* delegate = new TableCellDelegate();
    setItemDelegate(delegate);

    // Set the background color for table rows
    QString rowStyle = "QTableWidget::item {"
                       "    background-color: #F2F2F2;"
                       "}";
    setStyleSheet(rowStyle);

    // Set textAlignment left for the column headers
    for (int col = 0; col < columnNumber; ++col) {
        QTableWidgetItem* headerItem = horizontalHeaderItem(col);
        if (headerItem) {
            headerItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

}

void TableWidget::resize()
{
    // Отримуємо новий розмір віджета
    width = parentWidget()->width();
    resizeTable();
}

void TableWidget::fillWithData()
{
    std::vector<team> teams = Client::getInstance().GetTeams();
    // Встановлюємо кількість рядків у таблиці
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
        qDebug() << teams[i].getTeamName();
        // Додати значення відповідно до стовпців
        setItem(i, 0, new QTableWidgetItem(teams[i].getTeamName()));
        setItem(i, 1, new QTableWidgetItem(teams[i].getTeamLocation()));
        setItem(i, 2, new QTableWidgetItem("2022-12-12"));
        setItem(i, 3, new QTableWidgetItem(teams[i].getSubcategoryId()));
        setItem(i, 4, new QTableWidgetItem(teams[i].getSubcategoryId()));
    }
}

void TableWidget::resizeTable()
{
    int desireWidth = width - 20;
    setFixedWidth(desireWidth);
    double columnRatios[] = {0.2, 0.2, 0.15, 0.15, 0.15, 0.075, 0.075};

    for (int i = 0; i < columnNumber; i++) {
        int columnWidth = columnRatios[i] * desireWidth;
        setColumnWidth(i, columnWidth);
    }
}
