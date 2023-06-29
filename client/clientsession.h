#ifndef CLIENTSESSIONINFO_H
#define CLIENTSESSIONINFO_H

#include <string>

class ClientSession {
private:
    ClientSession();
    static ClientSession* instance;
    std::string key;
    std::string firstName;
    std::string lastName;
    std::string email;

public:
    static ClientSession* getInstance();
    static void deleteInstance();
    std::string getKey();
    void setKey(std::string key);
    std::string getFirstName();
    void setFirstName(std::string firstName);
    std::string getLastName();
    void setLastName(std::string lastName);
    std::string getEmail();
    void setEmail(std::string email);
};

#endif // CLIENTSESSIONINFO_H
