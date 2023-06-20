#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    Category();
    Category(int id, const QString& name);

    int getId() const;
    void setId(int id);

    const QString& getName() const;
    void setName(const QString& name);

private:
    int m_id;
    QString m_name;
};

#endif // CATEGORY_H
