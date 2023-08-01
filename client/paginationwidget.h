#ifndef PAGINATIONWIDGET_H
#define PAGINATIONWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QEvent>

class PaginationControl : public QFrame
{
    Q_OBJECT
public:
    PaginationControl(int items_count, int result_count);

    void setParameters(int items_count, int result_count);
    int getCurrentPage();

private:
    int max_buttons_count, current_page, pages_count, lvisible, rvisible, buttons_count;

    QHBoxLayout* layout, *clayout;

    std::vector<QLabel> page_buttons;
    QPushButton* left_arrow, *right_arrow;
    QLabel* show_text;

    QIcon larrow_icon, larrow_active_icon, rarrow_icon, rarrow_active_icon;

    void setCurrentPage(int new_page);
    void changeArrowsView();

private slots:
    void onLeftArrowClicked();
    void onRightArrowClicked();

signals:
    void currentPageChanged(int new_page);

};

class PaginationWidget : public QFrame
{
    Q_OBJECT
public:
    PaginationWidget(int items_count, int result_count);

    int getCurrentPage();
    int getResultCount();

    void setItemsCount(int items_count);

private:

    int items_count;

    QHBoxLayout* layout;
    QFrame *count_setter;
    PaginationControl *control;

    QLabel* text;
    QComboBox* count;

private slots:
    void onCurrentTextChanged(const QString& text);
    void onCurrentPageChanged(int page);

signals:
    void resultCountChanged();
    void pageChanged();

};

#endif // PAGINATIONWIDGET_H
