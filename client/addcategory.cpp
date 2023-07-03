#include "addcategory.h"
#include "ui_addcategory.h"

AddCategory::AddCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategory)
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

    connect(addPushButton.get(), &QPushButton::clicked, this, &AddCategory::addPushButtonClicked);
    connect(cancelPushButton.get(), &QPushButton::clicked, this, &AddCategory::cancelButtonClicked);
}

AddCategory::~AddCategory()
{
    delete ui;
}

QString AddCategory::getCategoryName() const
{
    return this->addCategoryLineEdit->text();
}

void AddCategory::initializeLayouts()
{
    genericGridLayout = std::make_unique<QGridLayout>(this);

    mainLabelHLayout = std::make_unique<QHBoxLayout>();
    nameLabelHLayout = std::make_unique<QHBoxLayout>();
    buttonsHLayout = std::make_unique<QHBoxLayout>();

    lineEditVLayout = std::make_unique<QVBoxLayout>();
    generalVLayout = std::make_unique<QVBoxLayout>();
}

void AddCategory::initializeButtons()
{
    cancelPushButton = std::make_unique<QPushButton>();
    addPushButton = std::make_unique<QPushButton>();
}

void AddCategory::initializeLabels()
{
    mainLabel = std::make_unique<QLabel>();
    nameLabel = std::make_unique<QLabel>();
}

void AddCategory::initializeLineEdits()
{
    addCategoryLineEdit = std::make_unique<QLineEdit>();
}

void AddCategory::initializeSpacers()
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

void AddCategory::mainLabelLayout()
{
    mainLabel->setText("Add new category");
    mainLabel->setStyleSheet("QLabel {"
                             "  font-size: 24px;"
                             "  font-weight: bold; }");

    mainLabelHLayout->addSpacerItem(mainLabelSpacer_1.get());
    mainLabelHLayout->addWidget(mainLabel.get());
    mainLabelHLayout->addSpacerItem(mainLabelSpacer_2.get());
}

void AddCategory::nameLabelLayout()
{
    nameLabel->setText("NAME");

    nameLabelHLayout->addWidget(nameLabel.get());
    nameLabelHLayout->addSpacerItem(nameLabelSpacer_1.get());

    lineEditLayout();
}

void AddCategory::lineEditLayout()
{
    addCategoryLineEdit->setPlaceholderText("Name your menu item");
    addCategoryLineEdit->setMinimumHeight(35);
    addCategoryLineEdit->setStyleSheet("padding-left: 15px;");

    lineEditVLayout->addLayout(nameLabelHLayout.get());
    lineEditVLayout->addWidget(addCategoryLineEdit.get());
}

void AddCategory::buttonsLayout()
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

void AddCategory::addPushButtonClicked()
{
    if(addCategoryLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Category Error", "Input name of a new category. Field can`t be empty!");
    }
    else
    {
        emit newButtonAdded(); // Emit the signal

        this->addCategoryLineEdit->clear();
        this->close();
    }
}

void AddCategory::cancelButtonClicked()
{
    this->close();
}
