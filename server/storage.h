#ifndef STORAGE_H
#define STORAGE_H
#pragma once



#include <map>
//#include "server.h"
#include <Poco/JWT/JWT.h>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include <QDebug>

class storage
{
public:
    static std::map<std::string,Poco::JWT::Token>TokenStorage;
    storage();
    static void AddToken(Poco::JWT::Token token,std::string key);
    static void ClearAllTokens();
    static Poco::JWT::Token GetTokenFromStorage(std::string key);
};

#endif // STORAGE_H
