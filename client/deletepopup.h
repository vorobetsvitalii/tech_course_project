#ifndef DELETEPOPUP_H
#define DELETEPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <memory>
#include <QGraphicsDropShadowEffect>
#include <QPainter>

#include "client.h"

namespace Ui {
class DeletePopup;
}
class DeletePopup : public QDialog
{
    Q_OBJECT

public:
    explicit DeletePopup(const QString& table_name, QWidget *parent = nullptr);
    QString MesageBoxStyle ="QMessageBox {"
                             "  background-color: white;"
                             "  border: none;"
                             "}"
                             "QMessageBox QLabel {"
                             "  color: black;"
                             "  font-size: 12px;"
                             "  margin-top:40px;"
                             "  border: none;"
                             "}"
                             "QMessageBox QPushButton {"
                             "  background-color: red;"
                             "  color: white;"
                             "  border: none;"
                             "  padding: 5px 30px;" // Adjust the padding for longer buttons
                             "  font-size: 14px;"
                             "}"
                             "QMessageBox QPushButton:hover {"
                             "  background-color: darkred;"
                             "}";
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
    ~DeletePopup();
private:
    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QVBoxLayout> mainLayout;
    std::unique_ptr<QVBoxLayout> iconLayout;
    std::unique_ptr<QLabel> iconLabel;
    std::unique_ptr<QLabel> categoryLabel;
    std::unique_ptr<QLabel> confirmationLabel;
    std::unique_ptr<QLabel> confirmationLabel1;
    std::unique_ptr<QPushButton> deleteButton;
    std::unique_ptr<QPushButton> cancelButton;
    std::unique_ptr<QFrame> line;
    void applyCustomMessageBoxStyle(QMessageBox& messageBox);
    void InitializingLabels();
    void LabelsLayout();
    void SpacerLayout();
    void InitializingButtons();
    void ButtonLayout();
    void InitializingLine();
    void LineLayout();
    QString table_name;
    static QString table_category;
    static QString table_subcategory;
    static QString table_team;
    Subcategory selectedSubcategory;

    Team selectedTeam;

    Category selectedCategory;
private slots:
    void deleteClicked();
    void cancelClicked();
};

#endif // DELETEPOPUP_H
