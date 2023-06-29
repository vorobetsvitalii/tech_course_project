#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <memory>

namespace Ui {
class AddCategory;
}

class AddCategory : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategory(QWidget *parent = nullptr);
    ~AddCategory();

    QString getCategoryName() const;

private:
    Ui::AddCategory *ui;

    std::unique_ptr<QGridLayout> genericGridLayout;

    std::unique_ptr<QHBoxLayout> mainLabelHLayout;
    std::unique_ptr<QHBoxLayout> nameLabelHLayout;
    std::unique_ptr<QHBoxLayout> buttonsHLayout;

    std::unique_ptr<QVBoxLayout> lineEditVLayout;
    std::unique_ptr<QVBoxLayout> generalVLayout;

    std::unique_ptr<QLabel> mainLabel;
    std::unique_ptr<QLabel> nameLabel;

    std::unique_ptr<QLineEdit> addCategoryLineEdit;

    std::unique_ptr<QPushButton> addPushButton;
    std::unique_ptr<QPushButton> cancelPushButton;

    std::unique_ptr<QSpacerItem> mainLabelSpacer_1;
    std::unique_ptr<QSpacerItem> mainLabelSpacer_2;
    std::unique_ptr<QSpacerItem> nameLabelSpacer_1;
    std::unique_ptr<QSpacerItem> buttonsSpacer_1;

    std::unique_ptr<QSpacerItem> outsideSpacer_1;
    std::unique_ptr<QSpacerItem> innerSpacer_1;
    std::unique_ptr<QSpacerItem> innerSpacer_2;
    std::unique_ptr<QSpacerItem> outsideSpacer_2;

    void initializeLayouts();
    void initializeButtons();
    void initializeLabels();
    void initializeLineEdits();
    void initializeSpacers();

    void mainLabelLayout();
    void nameLabelLayout();
    void lineEditLayout();
    void buttonsLayout();

signals:
    void newButtonAdded();

private slots:
    void addPushButtonClicked();
    void cancelButtonClicked();
};

#endif // ADDCATEGORY_H
