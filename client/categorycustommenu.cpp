#include "categorycustommenu.h"

CategoryCustomMenu::CategoryCustomMenu(QWidget *parent) : QMenu(parent)
{
    QAction *action1 = new QAction("Hide", this);
    QAction *action2 = new QAction("Delete", this);
    QAction *action3 = new QAction("Edit", this);

    connect(action1, &QAction::triggered, this, &CategoryCustomMenu::handleContextMenuAction);
    connect(action2, &QAction::triggered, this, &CategoryCustomMenu::handleContextMenuAction);
    connect(action3, &QAction::triggered, this, &CategoryCustomMenu::handleContextMenuAction);

    addAction(action1);
    addSeparator();
    addAction(action2);
    addSeparator();
    addAction(action3);

    this->setStyleSheet("font-size: 16px;"
                        "margin: 3px;"
                        "padding: 5px;"
                        "border: 1px solid #C4CED4;"
                        "background: white;"
                        "color: #333333;"
                        "font-size: 9pt;"
                        "font-weight: bold;"
                        "");
    categoriesList = Client::GetCategories();

}

void CategoryCustomMenu::setCategoryIndex(const int &index_)
{
    index = index_;
}

void CategoryCustomMenu::setTempCategoryButton(QPushButton* temp_category_button_)
{
    temp_category_button = temp_category_button_;
}

void CategoryCustomMenu::handleContextMenuRequested(const QPoint &pos)
{
    emit contextMenuRequested(pos);
}
void CategoryCustomMenu::onCategoryNameUpdated(const QString& newName)
{
    temp_category_button->setText(newName);
}
void CategoryCustomMenu::handleContextMenuAction()
{
    QAction *senderAction = qobject_cast<QAction*>(sender());

    if (senderAction)
    {
        if (senderAction->text() == "Hide")
        {
            if(temp_category_button->parentWidget()->layout()->count() <= 2)
            {
                QLabel* hiddenLabel = new QLabel("X");

                hiddenLabel->setStyleSheet("color: red; padding-left: 2px;");
                temp_category_button->parentWidget()->layout()->addWidget(hiddenLabel);
            }
            else
            {
                temp_category_button->parentWidget()->layout()->itemAt(2)->widget()->deleteLater();
            }
        }
        else if (senderAction->text() == "Delete")
        {
            if(temp_category_button != nullptr)
            {
                Category selectedCategory;
                for (const Category& category : categoriesList)
                {
                    if (category.getName() == temp_category_button->text().toStdString())
                    {
                        // Store the selected subcategory
                        selectedCategory = category;

                    }
                }
                DeletePopup deletePopup(deletePopup.getTableSubcategory(), this);
                deletePopup.setSelectedCategory(selectedCategory);
                deletePopup.setStyleSheet("border: none");
                deletePopup.exec();
                if(deletePopup.exec()== QDialog::Accepted){
                    temp_category_button->parentWidget()->deleteLater();
                }
            }
        }
        else if (senderAction->text() == "Edit")
        {
            Category selectedCategory;
            for (const Category& category : categoriesList)
            {
                if (category.getName() == temp_category_button->text().toStdString())
                {
                    // Store the selected category
                    selectedCategory = category;

                }
            }
            QString existingCategoryName = temp_category_button->text();
            EditPopup editPopup(existingCategoryName, editPopup.getTableCategory(), this);
            editPopup.setSelectedCategory(selectedCategory);
            // Connect a slot to handle the nameUpdated signal emitted from EditPopup
            editPopup.setStyleSheet("border: none");
            connect(&editPopup, &EditPopup::NameUpdated , this, &CategoryCustomMenu::onCategoryNameUpdated);
            editPopup.exec();
        }
    }
}

QPushButton* CategoryCustomMenu::temp_category_button = nullptr;
int CategoryCustomMenu::index = NULL;
