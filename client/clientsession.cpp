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
