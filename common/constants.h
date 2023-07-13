#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

class Constants
{
public:
    //API
    static const std::string loginApi;
    static const std::string logoutApi;
    static const std::string categoriesApi;
    static const std::string subcategoriesApi;
    static const std::string locationsGet;

    //JSON
    static const std::string categoriesArrayJson;
    static const std::string subcategoriesArrayJson;
};
#endif // CONSTANTS_H
