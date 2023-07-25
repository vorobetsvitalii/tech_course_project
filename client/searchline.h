#ifndef SEARCHLINE_H
#define SEARCHLINE_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class SearchLine : public QFrame
{
    Q_OBJECT

public:
    SearchLine();

private:
    QHBoxLayout* layout;
    QLineEdit* text;
    QLabel* search_icon_block;

private slots:
    void onTextEdited(const QString& text);

signals:
    void nameChanged(const QString& new_name);

};

#endif // SEARCHLINE_H
