#ifndef ADDTEAMS_H
#define ADDTEAMS_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <memory>

namespace Ui {
class AddTeams;
}

class AddTeams : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeams(QWidget *parent = nullptr);
    ~AddTeams();

    QString getTeamName() const;

private:
    Ui::AddTeams *ui;

    std::unique_ptr<QGridLayout> genericGridLayout;

    std::unique_ptr<QHBoxLayout> mainLabelHLayout;
    std::unique_ptr<QHBoxLayout> nameLabelHLayout;
    std::unique_ptr<QHBoxLayout> buttonsHLayout;

    std::unique_ptr<QVBoxLayout> lineEditVLayout;
    std::unique_ptr<QVBoxLayout> generalVLayout;

    std::unique_ptr<QLabel> mainLabel;
    std::unique_ptr<QLabel> nameLabel;

    std::unique_ptr<QLineEdit> addSubcategoryLineEdit;

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

#endif // ADDTEAMS_H
