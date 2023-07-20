#ifndef EDITPOPUP_H
#define EDITPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <memory>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>

#include "client.h"

namespace Ui {
class EditPopup;
}
class EditPopup : public QDialog
{
    Q_OBJECT

public:
    explicit EditPopup(const QString& existingName,const QString& table_name, QWidget *parent = nullptr);
    ~EditPopup();

    QString getName() const;
    void setName(const QString& name);
   static void applyCustomMessageBoxStyle(QMessageBox& messageBox);
    void InitializingLabels();
    void LabelsLayout();


    void InitializingButtons();
    void ButtonLayout();

    void InitializingLineEdit();
    void LineEditLayout();

    void ShadowEffect();

    void setSelectedCategory(const Category& category);
    void setSelectedSubcategory(const Subcategory& subcategory);

    void setSelectedTeam(const Team& team);


    static QString getTableCategory() {
        return table_category;
    }

    static QString getTableSubcategory() {
        return table_subcategory;
    }

    static QString getTableTeam() {
        return table_team;
    }
signals:

    void NameUpdated(const QString &newName);

private slots:
    void saveClicked();
    void cancelClicked();

private:
    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QVBoxLayout> mainLayout;
    std::unique_ptr<QLabel> iconLabel;
    std::unique_ptr<QLabel> mainLabel;
    std::unique_ptr<QLabel> confirmationLabel1;
    std::unique_ptr<QLineEdit> nameLineEdit;
    std::unique_ptr<QPushButton> saveButton;
    std::unique_ptr<QPushButton> cancelButton;
    QString originalName;
    std::unique_ptr<QMessageBox> confirmationBox;
    QString table_name;
    QString existingName;
    static QString table_category;
    static QString table_subcategory;
    static QString table_team;
    Subcategory selectedSubcategory;

    Team selectedTeam;

    Category selectedCategory;

};


#endif // EDITPOPUP_H
