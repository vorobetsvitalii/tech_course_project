#include "addsubcategory.h"
#include "ui_addsubcategory.h"

AddSubcategory::AddSubcategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSubcategory)
{
    ui->setupUi(this);

    this->resize(500, 250);
    this->setStyleSheet("font-family: Arial; background-color: white;");

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    initializeLayouts();
    initializeButtons();
    initializeLabels();
    initializeSpacers();
    initializeLineEdits();

    mainLabelLayout();
    nameLabelLayout();
    buttonsLayout();

    genericGridLayout->addLayout(mainLabelHLayout.get(), 0, 1);
    genericGridLayout->addLayout(lineEditVLayout.get(), 1, 1);
    genericGridLayout->addLayout(buttonsHLayout.get(), 3, 1);

    genericGridLayout->addItem(outsideSpacer_1.get(), 0, 0);
    genericGridLayout->addItem(innerSpacer_1.get(), 2, 1);
    genericGridLayout->addItem(innerSpacer_2.get(), 4, 1);
    genericGridLayout->addItem(outsideSpacer_2.get(), 0, 2);

    setLayout(genericGridLayout.get());

    connect(addPushButton.get(), &QPushButton::clicked, this, &AddSubcategory::addPushButtonClicked);
    connect(cancelPushButton.get(), &QPushButton::clicked, this, &AddSubcategory::cancelButtonClicked);
}

AddSubcategory::~AddSubcategory()
{
    delete ui;
}

QString AddSubcategory::getSubcategoryName() const
{
    return this->addSubcategoryLineEdit->text();
}

void AddSubcategory::initializeLayouts()
{
    genericGridLayout = std::make_unique<QGridLayout>(this);

    mainLabelHLayout = std::make_unique<QHBoxLayout>();
    nameLabelHLayout = std::make_unique<QHBoxLayout>();
    buttonsHLayout = std::make_unique<QHBoxLayout>();

    lineEditVLayout = std::make_unique<QVBoxLayout>();
    generalVLayout = std::make_unique<QVBoxLayout>();
}

void AddSubcategory::initializeButtons()
{
    cancelPushButton = std::make_unique<QPushButton>();
    addPushButton = std::make_unique<QPushButton>();
}

void AddSubcategory::initializeLabels()
{
    mainLabel = std::make_unique<QLabel>();
    nameLabel = std::make_unique<QLabel>();
}

void AddSubcategory::initializeLineEdits()
{
    addSubcategoryLineEdit = std::make_unique<QLineEdit>();
}

void AddSubcategory::initializeSpacers()
{
    mainLabelSpacer_1 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    mainLabelSpacer_2 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    nameLabelSpacer_1 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    buttonsSpacer_1 = std::make_unique<QSpacerItem>(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    outsideSpacer_1 = std::make_unique<QSpacerItem>(60, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    innerSpacer_1 = std::make_unique<QSpacerItem>(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    innerSpacer_2 = std::make_unique<QSpacerItem>(0, 25, QSizePolicy::Expanding, QSizePolicy::Fixed);
    outsideSpacer_2 = std::make_unique<QSpacerItem>(60, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void AddSubcategory::mainLabelLayout()
{
    mainLabel->setText("Add new subcategory");
    mainLabel->setStyleSheet("QLabel {"
                             "  font-size: 24px;"
                             "  font-weight: bold; }");

    mainLabelHLayout->addSpacerItem(mainLabelSpacer_1.get());
    mainLabelHLayout->addWidget(mainLabel.get());
    mainLabelHLayout->addSpacerItem(mainLabelSpacer_2.get());
}

void AddSubcategory::nameLabelLayout()
{
    nameLabel->setText("NAME");

    nameLabelHLayout->addWidget(nameLabel.get());
    nameLabelHLayout->addSpacerItem(nameLabelSpacer_1.get());

    lineEditLayout();
}

void AddSubcategory::lineEditLayout()
{
    addSubcategoryLineEdit->setPlaceholderText("Name your menu item");
    addSubcategoryLineEdit->setMinimumHeight(35);
    addSubcategoryLineEdit->setStyleSheet("padding-left: 15px;");

    lineEditVLayout->addLayout(nameLabelHLayout.get());
    lineEditVLayout->addWidget(addSubcategoryLineEdit.get());
}

void AddSubcategory::buttonsLayout()
{
    cancelPushButton->setText("Cancel");
    cancelPushButton->setMinimumSize(80, 30);
    cancelPushButton->setStyleSheet("background-color:"
                                    "   transparent;"
                                    "   color: red;"
                                    "   font-weight: bold;");

    addPushButton->setText("Add");
    addPushButton->setMinimumSize(80, 30);
    addPushButton->setStyleSheet("background-color:red;"
                                 "font-weight: bold;"
                                 "color: white;"
                                 "border: none;");

    buttonsHLayout->addSpacerItem(buttonsSpacer_1.get());
    buttonsHLayout->addWidget(cancelPushButton.get());
    buttonsHLayout->addWidget(addPushButton.get());
}

void AddSubcategory::addPushButtonClicked()
{
    if(addSubcategoryLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Subcategory Error", "Input name of a new subcategory. Field can`t be empty!");
    }
    else
    {
        emit newButtonAdded(); // Emit the signal

        this->addSubcategoryLineEdit->clear();
        this->close();
    }
}

void AddSubcategory::cancelButtonClicked()
{
    this->close();
}
