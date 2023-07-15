#include "teamCreator.h"



std::unique_ptr<Entity> TeamCreator::FactoryMethod() const
{
    return std::make_unique<team>();
}
