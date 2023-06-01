#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include <QHBoxLayout>

namespace Ui {
class AdminPage;
}

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

private:
    Ui::AdminPage *ui;
};

#endif // ADMINPAGE_H
