#ifndef TEAMCREATOR_H
#define TEAMCREATOR_H

#include "team.h"
#include "creator.h"
#include <memory>
class TeamCreator : public Creator
{
public:
    std::unique_ptr<Entity> FactoryMethod() const override;

};

#endif // TEAMCREATOR_H
