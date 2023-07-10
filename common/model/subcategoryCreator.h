#ifndef SUBCATEGORYCREATOR_H
#define SUBCATEGORYCREATOR_H

#include "Creator.h"
#include "subcategory.h"
#include <memory>

class SubcategoryCreator : public Creator {
public:
    std::unique_ptr<Entity> FactoryMethod() const override;
};

#endif // SUBCATEGORYCREATOR_H
