#ifndef IDATAMODEL_H
#define IDATAMODEL_H

#include <iostream>

class IDataModel
{
public:
    virtual ~IDataModel() {}

    virtual const std::string GetTable() const = 0;
    virtual void Create() = 0;
    virtual void Select(const std::string select_query) = 0;
    virtual void Update() = 0;
    virtual void Delete() = 0;
};

#endif // IDATAMODEL_H
