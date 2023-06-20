#include "category.h"

Category::Category()
    : m_id(0)
{
}

Category::Category(int id, const QString& name)
    : m_id(id), m_name(name)
{
}

int Category::getId() const
{
    return m_id;
}

void Category::setId(int id)
{
    m_id = id;
}

const QString& Category::getName() const
{
    return m_name;
}

void Category::setName(const QString& name)
{
    m_name = name;
}
