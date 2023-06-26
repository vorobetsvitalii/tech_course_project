#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>

class Category
{
private:
    int id;
    std::string name;
public:
    int getId() const;
    std::string getName() const;
    static Category fromJSON(const std::string& json);
    friend std::ostream& operator<<(std::ostream& os, const Category& category);
};

#endif // CATEGORY_H
