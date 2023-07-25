#include "searchline.h"

SearchLine::SearchLine()
{
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    text = new QLineEdit();
    text->setStyleSheet("border: none; font: 600 12px \"Open Sans\";");
    text->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    search_icon_block = new QLabel();
    search_icon_block->setPixmap(QPixmap("../img/search_icon.svg"));

    layout->addWidget(text);
    layout->addWidget(search_icon_block);

    this->setLayout(layout);
    this->setFixedHeight(36);

    connect(text, &QLineEdit::textEdited, this, &SearchLine::onTextEdited);

}

void SearchLine::onTextEdited(const QString& text)
{
    emit nameChanged(text);
}
