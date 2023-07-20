#include "customcontextmenu.h"

CustomContextMenu::CustomContextMenu(QWidget *parent) : QMenu(parent)
{
    QAction *action1 = new QAction("Hide", this);
    QAction *action2 = new QAction("Delete", this);
    QAction *action3 = new QAction("Edit", this);

    connect(action1, &QAction::triggered, this, &CustomContextMenu::handleContextMenuAction);
    connect(action2, &QAction::triggered, this, &CustomContextMenu::handleContextMenuAction);
    connect(action3, &QAction::triggered, this, &CustomContextMenu::handleContextMenuAction);

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
    subcategoriesList = Client::GetSubcategories();

}

void CustomContextMenu::setSubcategoryIndex(const int &index_)
{
    index = index_;
}

void CustomContextMenu::setTempSubcategoryButton(QPushButton* temp_subcategory_button_)
{
    temp_subcategory_button = temp_subcategory_button_;
}

void CustomContextMenu::handleContextMenuRequested(const QPoint &pos)
{
    emit contextMenuRequested(pos);
}
void CustomContextMenu::onSubcategoryNameUpdated(const QString& newName)
{
    temp_subcategory_button->setText(newName);
}
void CustomContextMenu::handleContextMenuAction()
{
    QAction *senderAction = qobject_cast<QAction*>(sender());

    if (senderAction)
    {
        if (senderAction->text() == "Hide")
        {
            qDebug() << "Hide action triggered!";
        }
        else if (senderAction->text() == "Delete")
        {
            if(temp_subcategory_button != nullptr)
            {
                Subcategory selectedSubcategory;
                for (const Subcategory& subcategory : subcategoriesList)
                {
                    if (subcategory.getName() == temp_subcategory_button->text().toStdString())
                    {
                        // Store the selected subcategory
                        selectedSubcategory = subcategory;

                    }
                }
                DeletePopup deletePopup(deletePopup.getTableSubcategory(), this);
                deletePopup.setSelectedSubcategory(selectedSubcategory);
                deletePopup.setStyleSheet("border: none");
                deletePopup.exec();
                if(deletePopup.exec()== QDialog::Accepted){
                temp_subcategory_button->parentWidget()->deleteLater();
                }
            }
        }
        else if (senderAction->text() == "Edit")
        {
              Subcategory selectedSubcategory;
                for (const Subcategory& subcategory : subcategoriesList)
                {
                    if (subcategory.getName() == temp_subcategory_button->text().toStdString())
                    {
                        // Store the selected subcategory
                        selectedSubcategory = subcategory;

                    }
                }
                QString existingSubcategoryName = temp_subcategory_button->text();
                EditPopup editPopup(existingSubcategoryName, editPopup.getTableSubcategory(), this);
                editPopup.setSelectedSubcategory(selectedSubcategory);
                // Connect a slot to handle the nameUpdated signal emitted from EditPopup
                editPopup.setStyleSheet("border: none");
                connect(&editPopup, &EditPopup::NameUpdated , this, &CustomContextMenu::onSubcategoryNameUpdated);
                editPopup.exec();


        }
    }
}

QPushButton* CustomContextMenu::temp_subcategory_button = nullptr;
int CustomContextMenu::index = NULL;
