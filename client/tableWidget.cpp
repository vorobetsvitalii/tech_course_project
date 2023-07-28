#include "tablewidget.h"


TableWidget::TableWidget(QWidget* parent) : QTableWidget(parent)
{
    setColumnCount(columnNumber);
    resizeTable();
    setShowGrid(false);

    verticalHeader()->setVisible(false);
    QStringList headerLabels = {"Teams", "Location", "Added at", "Category", "Subcategory", "", ""};
    setHorizontalHeaderLabels(headerLabels);

    teams = Client::getInstance().GetTeams();
    filteredTeams = teams;

    initializeCells();

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
    
    // Install the event filter and enable mouse tracking once for the whole table
    installEventFilter(this);
    setMouseTracking(true);
    hoveredRow = -1;

    initPagination();

    setPageResults(teams);

}

void TableWidget::resize()
{
    width = parentWidget()->width();
    qDebug() << width << " Resize";
    resizeTable();
}

void TableWidget::refreshPageResults(std::vector<Team> &teams_data)
{
    pagination->setItemsCount(teams_data.size());
    setPageResults(teams_data);
}

void TableWidget::setPageResults(std::vector<Team> &teams_data)
{
    std::vector<Team> page;
    int l = std::min((int)teams_data.size(), pagination->getCurrentPage() * pagination->getResultCount());
    int rows = std::min((int)teams_data.size() - l, pagination->getResultCount());
    for(int i = 0; i < rows; i++)
        page.push_back(teams_data[l + i]);

    fillWithData(page);
}

void TableWidget::fillWithData(std::vector<Team> &teams_page)
{
    QIcon deleteIcon("../img/Delete_icon.png");

    setRowCount(teams_page.size());

    deleteIcons.clear();

    // Додати дані до таблиці

    for (int i = 0; i < rowCount(); ++i)
    {
        Team& team = teams_page[i];
        qDebug() << team.getTeamName() +" "+QString::number(team.getTeamLocation())+" "+team.getDate()+" "+QString::number(team.getSubcategoryId())+" "+QString::number(team.getSubcategoryId())+" ";

        int locationId = team.getTeamLocation();
        int subcategoryId = team.getSubcategoryId();
        int categoryId;
        QString locationName = FindLocationById(locationId);
        QString subcategoryName = FindSubcategoryById(subcategoryId, &categoryId);
        QString categoryName = FindCategoryById(categoryId);

        setItem(i, 0, new QTableWidgetItem(team.getTeamName()));
        setItem(i, 1, new QTableWidgetItem(locationName));
        setItem(i, 2, new QTableWidgetItem(team.getDate().left(10)));
        setItem(i, 3, new QTableWidgetItem(categoryName));
        setItem(i, 4, new QTableWidgetItem(subcategoryName));

        deleteIcons.push_back(deleteIcon);

        setupRowWidgets(i);

    }
}

void TableWidget::filterTeams(QString name = "", int locationId = 0, int categoryId = 0, int subcategoryId = 0)
{
    auto isTeamMatching = [&](Team& team) {
        int teamLocationId = team.getTeamLocation();
        int teamSubcategoryId = team.getSubcategoryId();
        int teamCategoryId = FindCategoryIdBySubcategoryId(team.getSubcategoryId());

        if(team.getTeamName().indexOf(name) == -1)
            return false;

        if (locationId != 0 && teamLocationId != locationId)
            return false;

        if (categoryId != 0 && teamCategoryId != categoryId)
            return false;

        if (subcategoryId != 0 && teamSubcategoryId != subcategoryId)
            return false;

        return true;
    };

    filteredTeams.clear();

    for (Team& team : teams)
    {
       if (isTeamMatching(team))
       {
            filteredTeams.push_back(team);
       }
    }

    refreshPageResults(filteredTeams);
}

void TableWidget::searchTeamByName(const QString& name)
{
    filterTeams(name);
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

void TableWidget::showEvent(QShowEvent* event)
{
    resize();
    qDebug() << "showEvent";
    QTableWidget::showEvent(event);
}

void TableWidget::initializeCells() {
    for (int row = 0; row < rowCount(); ++row) {
        for (int col = 0; col < columnNumber - 2; ++col) {
            QTableWidgetItem* tableItem = item(row, col);
            if (tableItem) {
                tableItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            }
        }
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
    for (const auto& subcategory : TeamsUI::SubCategoriesAll) {
        if (subcategory.getId() == id) {
            *categoryId = subcategory.getCategoryId();
            subcategoryName = QString::fromStdString(subcategory.getName());
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

int FindCategoryIdBySubcategoryId(int id) {
    int categoryId;
    for (const auto& subcategory : TeamsUI::SubCategoriesAll) {
        if (subcategory.getId() == id) {
            categoryId = subcategory.getCategoryId();
            break;
        }
    }
    return categoryId;
}

void TableWidget::editButtonClicked(int row)
{
    // Get the data from the selected row
    QString teamName = item(row, 0)->text();


    Team selectedTeam;
    std::vector<Team> teamsList = Client::GetTeams();
    for (Team& team : teamsList)
    {
        if (team.getTeamName() == teamName)
        {
            selectedTeam = team;

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

    Team selectedTeam;
    for (int i = 0; i < teams.size(); ++i)
    {
        if (teams[i].getTeamName() == teamName)
        {
            selectedTeam = teams[i];
            teams.erase(teams.begin() + i);
            break;
        }
    }

    for (int i = 0; i < filteredTeams.size(); ++i)
    {
        if (filteredTeams[i].getTeamName() == teamName)
        {
            filteredTeams.erase(filteredTeams.begin() + i);
            break;
        }
    }

    DeletePopup deletePopup(deletePopup.getTableTeam(), this);
    deletePopup.setSelectedTeam(selectedTeam);
    deletePopup.setStyleSheet("border: none");
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

void TableWidget::initPagination()
{
    pagination = std::unique_ptr<PaginationWidget>(new PaginationWidget(filteredTeams.size(), 10));
    connect(pagination.get(), &PaginationWidget::resultCountChanged, this, &TableWidget::onResultCountChanged);
    connect(pagination.get(), &PaginationWidget::pageChanged, this, &TableWidget::onPageChanged);
}

PaginationWidget* TableWidget::getPagination()
{
    return pagination.get();
}

void TableWidget::onPageChanged()
{
    setPageResults(filteredTeams);
}

void TableWidget::onResultCountChanged()
{
    refreshPageResults(filteredTeams);
}