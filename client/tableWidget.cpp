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
                        "    color: black;"
                       "}";
    setStyleSheet(rowStyle);

    for (int col = 0; col < columnNumber; ++col) {
        QTableWidgetItem* headerItem = horizontalHeaderItem(col);
        if (headerItem) {
            headerItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }
    isRowHovered = false;
    for (int i = 0; i < rowCount(); ++i) {
        setupRowWidgets(i);


    }
    // Install the event filter and enable mouse tracking once for the whole table
    installEventFilter(this);
    setMouseTracking(true);
    hoveredRow = -1;

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


    QIcon deleteIcon("../img/Delete_icon.png");
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

       deleteIcons.push_back(deleteIcon);

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
void TableWidget::editButtonClicked(int row)
{
    // Get the data from the selected row
    QString teamName = item(row, 0)->text();

    team selectedTeam;
    std::vector<team> teamsList = Client::GetTeams();
    for (team& Team : teamsList)
    {
        if (Team.getTeamName() == teamName)
        {
            selectedTeam = Team;
        }
    }
    EditPopup editPopup(teamName,editPopup.getTableTeam(), this);
    editPopup.setName(teamName);
    editPopup.setSelectedTeam(selectedTeam);

    // Connect the signal from the edit popup to update the data in the table widget
    connect(&editPopup, &EditPopup::NameUpdated, this, [this, row](const QString& newName) {
        QTableWidgetItem* nameItem = item(row, 0);
        if (nameItem) {
            nameItem->setText(newName);
        }
    });
    editPopup.exec();

}

void TableWidget::deleteButtonClicked(int row)
{
    // Get the team name from the first column in the selected row
    QTableWidgetItem* nameItem = item(row, 0);
    if (!nameItem) {
        return; // No valid data in the first column
    }

    QString teamName = nameItem->text();

        team selectedTeam;
        std::vector<team> teamsList= Client::GetTeams();
        for (team& Team : teamsList)
        {
            if (Team.getTeamName() == teamName)
            {
                // Store the selected team
                selectedTeam = Team;

            }
        }
        DeletePopup deletePopup(deletePopup.getTableTeam(), this);
        deletePopup.setSelectedTeam(selectedTeam);
        deletePopup.setStyleSheet("border: none");
        deletePopup.exec();
        if (deletePopup.exec() == QDialog::Accepted) {
            removeRow(row);
        }

}
void TableWidget::setupRowWidgets(int row)
{
    // QLabel для іконки видалення (по замовчуванню невидимий)
    QLabel* iconLabel = new QLabel(this);
    iconLabel->setPixmap(deleteIcons.at(row).pixmap(20, 20)); // Adjust the pixmap size as needed
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet(" background-color: #F2F2F2;");

    iconLabel->hide();

    iconLabel->installEventFilter(this);

    QPushButton* editButton = new QPushButton("Edit", this);
    editButton->setStyleSheet("background-color: transparent; border: none; color: red; font-size: 12px;");
    editButton->setProperty("row", row); // Store the row index as a property in the widget

    editButton->hide();

    // Встановлюємо QLabel та QPushButton як вміст комірки у останньому стовпці
    setCellWidget(row, columnNumber - 1, iconLabel);
    setCellWidget(row, columnNumber - 2, editButton);
    iconLabel->setVisible(false);
    editButton->setVisible(false);
    connect(editButton, &QPushButton::clicked, this, [this, row]() {
        editButtonClicked(row);
    });

    connect(iconLabel, &QLabel::linkActivated, this, [this, row]() {
        deleteButtonClicked(row);
    });
}


void TableWidget::updateRowWidgetsVisibility(int row)
{
    for (int r = 0; r < rowCount(); ++r) {
        QWidget* iconLabel = cellWidget(r, columnNumber - 1);
        if (iconLabel) {
            iconLabel->setVisible(r == row);
        }
        QWidget* editButton = cellWidget(r, columnNumber - 2);
        if (editButton) {
            editButton->setVisible(r == row);
        }
    }
}

bool TableWidget::viewportEvent(QEvent* event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        int row = rowAt(mouseEvent->pos().y());
        if (row >= 0 && row < rowCount()) {
            hoveredRow = row;
            updateRowWidgetsVisibility(hoveredRow);
        }
    } else if (event->type() == QEvent::Leave) {
        hoveredRow = -1; // Reset hovered row
        updateRowWidgetsVisibility(hoveredRow);
    }else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        int row = rowAt(mouseEvent->pos().y());
        if (row >= 0 && row < rowCount()) {
            QWidget* deleteIconLabel = cellWidget(row, columnNumber - 1);
            if (deleteIconLabel && deleteIconLabel->underMouse()) {
                // If the click occurred on the delete icon, call the deleteButtonClicked function
                deleteButtonClicked(row);
            }
        }
    }

    // Call the base class event handler
    return QTableWidget::viewportEvent(event);
}

