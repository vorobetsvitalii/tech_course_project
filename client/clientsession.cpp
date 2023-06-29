#include "clientsession.h"

ClientSession* ClientSession::instance = nullptr;

ClientSession::ClientSession() {

}

ClientSession* ClientSession::getInstance() {
    if(instance == nullptr) {
        instance = new ClientSession();
    }
    return instance;
}

void ClientSession::deleteInstance() {
    if(instance != nullptr)
        delete instance;
    instance = nullptr;
}

void ClientSession::setKey(std::string key) {
    this->key = key;
}
std::string ClientSession::getKey() {
    return this->key;
}

void ClientSession::setFirstName(std::string firstName) {
    this->firstName = firstName;
}
std::string ClientSession::getFirstName() {
    return this->firstName;
}

void ClientSession::setLastName(std::string lastName) {
    this->lastName = lastName;
}
std::string ClientSession::getLastName() {
    return this->lastName;
}

void ClientSession::setEmail(std::string email) {
    this->email = email;
}
std::string ClientSession::getEmail() {
    return this->email;
}
