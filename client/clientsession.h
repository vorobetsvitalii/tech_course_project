#ifndef CLIENTSESSIONINFO_H
#define CLIENTSESSIONINFO_H

#include <string>

class ClientSession {
private:
    ClientSession();
    static ClientSession* instance;
    std::string key;

public:
    static ClientSession* getInstance();
    static void deleteInstance();
    void setKey(std::string key);
    std::string getKey();
};

#endif // CLIENTSESSIONINFO_H
