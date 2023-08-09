#include "paginationwidget.h"

PaginationControl::PaginationControl(int items_count, int result_count)
{
    this->setStyleSheet(this->objectName() + " QPushButton {"
                        "background: none;"
                        "border: none; }");


    larrow_icon = QIcon("../img/left-arrow-pagination.svg");
    larrow_active_icon = QIcon("../img/left-arrow-active-pagination.svg");
    rarrow_icon = QIcon("../img/right-arrow-pagination.svg");
    rarrow_active_icon = QIcon("../img/right-arrow-active-pagination.svg");

    layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    clayout = new QHBoxLayout();
    clayout->setSpacing(0);
    clayout->setContentsMargins(0, 0, 0, 0);

    left_arrow = new QPushButton("");
    left_arrow->setCursor(Qt::PointingHandCursor);
    connect(left_arrow, &QPushButton::clicked, this, &PaginationControl::onLeftArrowClicked);

    right_arrow = new QPushButton("");
    right_arrow->setCursor(Qt::PointingHandCursor);
    connect(right_arrow, &QPushButton::clicked, this, &PaginationControl::onRightArrowClicked);

    show_text = new QLabel();
    show_text->setStyleSheet("margin-left: 5px; color: #B2BBC5; font: 400 12px \"Open Sans\";");

    layout->addWidget(left_arrow);
    layout->addLayout(clayout);
    layout->addWidget(right_arrow);
    layout->addStretch(1);
    layout->addWidget(show_text);

    setParameters(items_count, result_count);

}

void PaginationControl::setParameters(int items_count, int result_count)
{
    pages_count = std::max(1, (int)std::ceil((double)items_count / result_count));
    max_buttons_count = 5;
    current_page = lvisible = 0;
    buttons_count = std::min(max_buttons_count, pages_count);
    rvisible = buttons_count - 1;

    page_buttons = std::vector<QLabel>(pages_count);
    for(int i = 0; i < page_buttons.size(); i++)
    {
        page_buttons[i].setText(QString::number(i+1));
        page_buttons[i].setStyleSheet("font: 500 12px \"Open Sans\"; color: #5C7694; margin:0px 2px 0px 2px;");
        page_buttons[i].setCursor(Qt::PointingHandCursor);
        
        clayout->addWidget(&page_buttons[i], Qt::AlignJustify);
        if(i < lvisible || i > rvisible) page_buttons[i].setHidden(true);
    }
    page_buttons[current_page].setStyleSheet("font: 700 12px \"Open Sans\"; color: #6F7983; margin:0px 2px 0px 2px;");

    show_text->setText(QString::number(lvisible + 1) + "-" + QString::number(rvisible + 1) +
                       " of " + QString::number(pages_count) + " results");
    changeArrowsView();

}

void PaginationControl::setCurrentPage(int new_page)
{
    if(new_page < 0 || new_page > pages_count) return;

    page_buttons[current_page].setStyleSheet("font: 500 12px \"Open Sans\"; color: #5C7694; margin:0px 2px 0px 2px;");
    page_buttons[new_page].setStyleSheet("font: 700 12px \"Open Sans\"; color: #6F7983; margin:0px 2px 0px 2px;");

    if(new_page > rvisible || new_page < lvisible)
    {
        for(int i = lvisible; i <= rvisible; i++)
            page_buttons[i].hide();

        if(new_page > rvisible)
        {
            lvisible = std::max(0, new_page - buttons_count + 1);
            rvisible = new_page;
        }
        else if(new_page < lvisible)
        {
            lvisible = new_page;
            rvisible = std::min(pages_count - 1, new_page + buttons_count - 1);
        }

        for(int i = lvisible; i <= rvisible; i++)
            page_buttons[i].show();
    }

    current_page = new_page;
    show_text->setText(show_text->text().replace(QRegularExpression("^(\\d*)-(\\d*)"), QString::number(lvisible + 1) + "-" + QString::number(rvisible + 1)));

    emit currentPageChanged(new_page);

}

int PaginationControl::getCurrentPage()
{
    return current_page;
}

void PaginationControl::changeArrowsView()
{
    if(current_page != 0)
        left_arrow->setIcon(larrow_active_icon);
    else
        left_arrow->setIcon(larrow_icon);

    if(current_page != pages_count - 1)
        right_arrow->setIcon(rarrow_active_icon);
    else
        right_arrow->setIcon(rarrow_icon);
}

void PaginationControl::onLeftArrowClicked()
{
    if(current_page > 0)
    {
        setCurrentPage(current_page - 1);
        changeArrowsView();
    }


}

void PaginationControl::onRightArrowClicked()
{
    if(current_page < pages_count - 1)
    {
        setCurrentPage(current_page + 1);
        changeArrowsView();
    }

}

PaginationWidget::PaginationWidget(int items_count, int result_count)
{
    this->items_count = items_count;

    layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setFixedHeight(40);

    // Control
    control = new PaginationControl(items_count, result_count);

    // Count setter
    count_setter = new QFrame();
    QHBoxLayout* res_layout = new QHBoxLayout(count_setter);
    res_layout->setSpacing(0);
    res_layout->setContentsMargins(0, 0, 0, 0);

    text = new QLabel("Result per page");
    text->setStyleSheet("color: #B2BBC5; font: 500 12px \"Open Sans\"; margin-right: 15px;");

    count = new QComboBox();
    count->addItems({"10", "20", "45", "90"});
    count->setObjectName("resultCountBox");
    count->setStyleSheet("#resultCountBox {"
                         " font: 500 12px \"Open Sans\"; "
                         " border: 1px solid #D9E1E9; "
                         " padding: 1px 2px 1px 2px;}"
                         "#resultCountBox::drop-down {"
                         " background: none;"
                         " border: none; "
                         " padding: none; margin: none; }"
                         "#resultCountBox QAbstractItemView {"
                         " border: 1px solid #D9E1E9;"
                         " border-radius: 0; }"
                         "#resultCountBox::down-arrow { "
                         " image: url(../img/drop_icon.svg); "
                         " background-color: white; "
                         " border: none; }");
    count->setCurrentText(QString::number(result_count));

    res_layout->addWidget(text);
    res_layout->addWidget(count);

    layout->addSpacing(15);
    layout->addWidget(control);
    layout->addStretch(1);
    layout->addWidget(count_setter);
    layout->addSpacing(15);

    connect(count, &QComboBox::currentTextChanged, this, &PaginationWidget::onCurrentTextChanged);
    connect(control, &PaginationControl::currentPageChanged, this, &PaginationWidget::onCurrentPageChanged);

    this->setObjectName("paginationWidget");
    this->setStyleSheet("#paginationWidget {"
                        " background-color: white;"
                        " border: 1px solid #D4D9E2;"
                        " border-top: none; }");

}

int PaginationWidget::getCurrentPage()
{
    return control->getCurrentPage();
}

int PaginationWidget::getResultCount()
{
    return count->currentText().toInt();
}

void PaginationWidget::setItemsCount(int items_count)
{
    control->setParameters(items_count, getResultCount());
}

void PaginationWidget::onCurrentTextChanged(const QString &text)
{
    int result_count = text.toInt();
    control->setParameters(items_count, result_count);
    emit resultCountChanged();
}

void PaginationWidget::onCurrentPageChanged(int page)
{
    emit pageChanged();
}
