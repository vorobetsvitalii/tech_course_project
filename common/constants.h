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
    static const std::string teamApi;
    static const std::string Port;
    static const std::string IP;
    //JSON
    static const std::string categoriesArrayJson;
    static const std::string subcategoriesArrayJson;
    static const std::string TeamsArrayJson;
};
#endif // CONSTANTS_H
