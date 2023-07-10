#ifndef CATEGORYCREATOR_H
#define CATEGORYCREATOR_H

#include "creator.h"
#include "category.h"
#include <memory>

class CategoryCreator : public Creator {
public:
    std::unique_ptr<Entity> FactoryMethod() const override;
};

#endif // CATEGORYCREATOR_H
