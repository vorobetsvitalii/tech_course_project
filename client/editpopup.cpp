#include "editpopup.h"
#include <QMessageBox>

EditPopup::EditPopup(const QString& existingName,const QString& table_name, QWidget *parent) : QDialog(parent),table_name(table_name), originalName(existingName)
{
    setWindowTitle("Edit");
    setFixedSize(500, 250);
    setStyleSheet("font-family: Arial; background-color: white;");

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    mainLayout=std::make_unique<QVBoxLayout>(this);
    mainLayout->setContentsMargins(50, 50, 50, 20);


    InitializingLabels();
    LabelsLayout();

    InitializingLineEdit();
    LineEditLayout();

    InitializingButtons();
    ButtonLayout();


    connect(saveButton.get(), &QPushButton::clicked, this, &EditPopup::saveClicked);
    connect(cancelButton.get(), &QPushButton::clicked, this, &EditPopup::cancelClicked);

    setLayout(mainLayout.get());

    ShadowEffect();
    setName(existingName);
}

EditPopup::~EditPopup() {}

QString EditPopup::table_category = "Category";
QString EditPopup::table_subcategory = "Subcategory";
QString EditPopup::table_team = "Team";


void EditPopup::InitializingLabels(){
    mainLabel = std::make_unique<QLabel>("Edit "+ table_name, this);
    mainLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    confirmationLabel1 = std::make_unique<QLabel>("Edit name:", this);
    confirmationLabel1->setStyleSheet("font-size: 15px");

}

void EditPopup::LabelsLayout(){
    mainLayout->addWidget(mainLabel.get(), 0, Qt::AlignCenter);
    mainLayout->addWidget(confirmationLabel1.get(), 0, Qt::AlignLeft);

}
void EditPopup::InitializingLineEdit(){

    nameLineEdit = std::make_unique<QLineEdit>(this);
    nameLineEdit->setStyleSheet("font-size: 16px;");
    nameLineEdit->setMinimumSize(400, 40);

}
void EditPopup::LineEditLayout(){
    mainLayout->addWidget(nameLineEdit.get(), 0, Qt::AlignCenter);
    mainLayout->addSpacing(20);

}
void EditPopup::InitializingButtons(){
    saveButton = std::make_unique<QPushButton>("Save", this);
    saveButton->setFixedSize(150, 35);
    saveButton->setStyleSheet("background-color: red; color: white; border: none; font-size: 15px");

    cancelButton = std::make_unique<QPushButton>("Cancel", this);
    cancelButton->setFixedSize(150, 35);
    cancelButton->setStyleSheet("background-color: white; color: red; border: none; font-size: 15px");


}

void EditPopup::ButtonLayout(){
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton.get());
    buttonLayout->addWidget(saveButton.get());

    mainLayout->addLayout(buttonLayout);
}
void EditPopup::ShadowEffect(){
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 0);
    setGraphicsEffect(shadowEffect);
}
QString EditPopup::getName() const
{
    return nameLineEdit->text();
}

void EditPopup::setName(const QString& name)
{
    nameLineEdit->setText(name);
}

void EditPopup::saveClicked()
{
    QString newName = nameLineEdit->text();
    QMessageBox confirmationBox(this);
    confirmationBox.setWindowTitle("Confirmation");
    confirmationBox.setText("Are you sure you want to save the changes?");
    confirmationBox.setIcon(QMessageBox::Question);
    confirmationBox.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    applyCustomMessageBoxStyle(confirmationBox);
    confirmationBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmationBox.setDefaultButton(QMessageBox::No);

    int result = confirmationBox.exec();

    if (result == QMessageBox::Yes) {
        //close();
        if(table_name==table_subcategory){
            selectedSubcategory.setName(newName.toStdString());
            Client::getInstance().EditSubcategory(selectedSubcategory);
        }else if (table_name == table_team) {
            selectedTeam.setTeamName(newName);
            Client::getInstance().EditTeam(selectedTeam);
        }else if (table_name == table_category) {
            selectedCategory.setName(newName.toStdString());
            Client::getInstance().EditCategory(selectedCategory);
        }
        emit NameUpdated(newName); // Emit the nameUpdated signal with the new name
        close();
        QMessageBox successBox;
        successBox.setWindowTitle("Success");
        successBox.setText("Changes have been saved.");
        successBox.setIcon(QMessageBox::Information);
        applyCustomMessageBoxStyle(successBox);
        successBox.exec();
        accept();
    }
}

void EditPopup::cancelClicked()
{
  close();
}
void EditPopup::applyCustomMessageBoxStyle(QMessageBox& messageBox)
{
    messageBox.setStyleSheet("QMessageBox {"
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
                             "}");
    messageBox.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}
void EditPopup::setSelectedCategory(const Category& category){

    selectedCategory = category;

}
void EditPopup::setSelectedSubcategory(const Subcategory& subcategory)
{
    selectedSubcategory = subcategory;
}


void EditPopup::setSelectedTeam(const Team& team)
{
    selectedTeam = team;
}

/*void DeletePopup::setSelectedCategory(const Category& category)
{
    selectedCategory = category;
}*/
