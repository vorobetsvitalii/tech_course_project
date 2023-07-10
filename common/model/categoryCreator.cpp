#include "categoryCreator.h"

std::unique_ptr<Entity> CategoryCreator::FactoryMethod() const {
    return std::make_unique<Category>();
}
