#include "subcategoryCreator.h"

std::unique_ptr<Entity> SubcategoryCreator::FactoryMethod() const {
    return std::make_unique<Subcategory>();
}
