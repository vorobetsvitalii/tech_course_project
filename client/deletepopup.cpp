#include "deletepopup.h"

DeletePopup::DeletePopup(const QString& table_name, QWidget *parent)
    : QDialog(parent), table_name(table_name)
{
    this->resize(500, 250);
    this->setMaximumSize(500, 250);
    this->setStyleSheet("font-family: Arial; background-color: white;");

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    mainLayout=std::make_unique<QVBoxLayout>(this);
    mainLayout->setContentsMargins(0, 0, 0,20);

    InitializingLabels();
    LabelsLayout();

    SpacerLayout();

    InitializingLine();
    LineLayout();

    InitializingButtons();
    ButtonLayout();


    connect(deleteButton.get(), &QPushButton::clicked, this, &DeletePopup::deleteClicked);
    connect(cancelButton.get(), &QPushButton::clicked, this, &DeletePopup::cancelClicked);
}



DeletePopup::~DeletePopup() {}

QString DeletePopup::table_category = "Category";
QString DeletePopup::table_subcategory = "Subcategory";
QString DeletePopup::table_team = "Team";


void DeletePopup::InitializingLabels(){

    iconLabel = std::make_unique<QLabel>(this);
    iconLabel->setPixmap(QPixmap("../img/DeletePopup_icon.png"));

    confirmationLabel = std::make_unique<QLabel>("You are about to delete this " + table_name, this);
    confirmationLabel->setStyleSheet("font-weight: bold;font-size:18px");

    confirmationLabel1 = std::make_unique<QLabel>("Are you sure?", this);
    confirmationLabel1->setStyleSheet("font-size:16px");
}

void DeletePopup::LabelsLayout(){
    mainLayout->addSpacing(20);
    mainLayout->addWidget(iconLabel.get(), 0, Qt::AlignCenter);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(confirmationLabel.get(), 0, Qt::AlignCenter);
    mainLayout->addWidget(confirmationLabel1.get(), 0, Qt::AlignCenter);

}

void DeletePopup::SpacerLayout(){
    QVBoxLayout* spacerLayout = new QVBoxLayout;
    spacerLayout->addStretch();
    mainLayout->addLayout(spacerLayout);
}

void DeletePopup::applyCustomMessageBoxStyle(QMessageBox& messageBox)
{
    messageBox.setStyleSheet(MesageBoxStyle);
    messageBox.setMinimumSize(600, 300);
    messageBox.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

void DeletePopup::InitializingButtons(){
    deleteButton = std::make_unique<QPushButton>("Delete", this);
    deleteButton->setFixedSize(150, 35);
    deleteButton->setStyleSheet("background-color: red; color: white;border: none;font-size:14px");

    cancelButton = std::make_unique<QPushButton>("Cancel", this);
    cancelButton->setFixedSize(150, 35);
    cancelButton->setStyleSheet("background-color: white; color:red;border: none;font-size:14px");

}

void DeletePopup::ButtonLayout(){
    mainLayout->addSpacing(10);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(cancelButton.get(),0,Qt::AlignRight);
    buttonLayout->addWidget(deleteButton.get(),0,Qt::AlignRight);
    buttonLayout->setContentsMargins(190, 0, 30,0);
    mainLayout->addLayout(buttonLayout);
}

void DeletePopup::InitializingLine(){
    // Add a horizontal line separating the buttons
    line =  std::make_unique<QFrame>(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(0);
    line->setStyleSheet("background-color: #EEEEEE");
}

void DeletePopup::LineLayout(){

    QHBoxLayout* lineLayout = new QHBoxLayout;

    lineLayout->addWidget(line.get());

    mainLayout->addLayout(lineLayout);
}

void DeletePopup::deleteClicked()
{
    QDialog confirmationDialog(this);
    confirmationDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    confirmationDialog.setStyleSheet("background-color: white; border: none;");

    QLabel titleLabel("Confirmation", &confirmationDialog);
    titleLabel.setStyleSheet("font-size: 16px; font-weight: bold;");

    QLabel messageLabel("Are you sure you want to delete?", &confirmationDialog);
    messageLabel.setStyleSheet("font-size: 15px;");

    QPushButton yesButton("Yes", &confirmationDialog);
    yesButton.setStyleSheet("background-color: red; color: white; border: none; padding: 8px 45px; font-size: 14px;");

    QPushButton noButton("No", &confirmationDialog);
    noButton.setStyleSheet("background-color: white; color: red; border: none; padding: 8px 45px; font-size: 14px;");

    QVBoxLayout layout(&confirmationDialog);
    layout.addWidget(&titleLabel, 0, Qt::AlignCenter);
    layout.addWidget(&messageLabel, 0, Qt::AlignCenter);
    layout.addWidget(&yesButton, 0, Qt::AlignCenter);
    layout.addWidget(&noButton, 0, Qt::AlignCenter);

    confirmationDialog.setMinimumSize(500, 250);
    confirmationDialog.setMaximumSize(500, 250);

    connect(&yesButton, &QPushButton::clicked, &confirmationDialog, &QDialog::accept);
    connect(&noButton, &QPushButton::clicked, &confirmationDialog, &QDialog::reject);

    int result = confirmationDialog.exec();

    if (result == QDialog::Accepted) {
        if(table_name==table_subcategory){
             Client::getInstance().DeleteSubcategory(selectedSubcategory);
        }else if (table_name == table_team) {
             // Delete the selected team
             Client::getInstance().DeleteTeam(selectedTeam);
        }else if (table_name == table_category) {
             Client::getInstance().DeleteCategory(selectedCategory);
        // Delete the selected category, subcategory, or team
        QMessageBox deletionBox(this);
        deletionBox.setWindowTitle("Deleted");
        deletionBox.setText("Selected "+ table_name +" has been deleted.");
        deletionBox.setIcon(QMessageBox::Information);

        applyCustomMessageBoxStyle(deletionBox);
        deletionBox.setMinimumSize(600,300);
        deletionBox.exec();
        accept();
    }
  }
}

void DeletePopup::setSelectedCategory(const Category& category){

  selectedCategory = category;

}
void DeletePopup::setSelectedSubcategory(const Subcategory& subcategory){
  selectedSubcategory = subcategory;
}

void DeletePopup::setSelectedTeam(const team& team)
{
  selectedTeam = team;
}

/*void DeletePopup::setSelectedCategory(const Category& category)
{
    selectedCategory = category;
}*/

void DeletePopup::cancelClicked()
{
  close();
}
