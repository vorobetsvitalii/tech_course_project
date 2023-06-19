#include "storage.h"


std::map<std::string, Poco::JWT::Token> storage::TokenStorage;
storage::storage()
{

}

void storage::AddToken(Poco::JWT::Token token,std::string key)
{
    qDebug()<<key;
    TokenStorage.insert(std::make_pair(key, token));
}

void storage::DeleteTokenByKey(std::string key)
{
    if(TokenStorage.find(key) != TokenStorage.end()) TokenStorage.erase(key);
}

Poco::JWT::Token storage::GetTokenFromStorage(std::string key)
{
    return TokenStorage[key];
}
