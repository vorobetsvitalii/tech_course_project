#ifndef CREATOR_H
#define CREATOR_H

#include <memory>
#include "../interface/IJsonSerializable.h"
#include "entity.h"

class Creator {
public:
    virtual ~Creator() {}
    virtual std::unique_ptr<Entity> FactoryMethod() const = 0;
};

#endif // CREATOR_H
