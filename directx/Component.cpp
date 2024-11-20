#include "Component.h"

Component::Component(String name, ComponentType type, GameObject* owner)
    : name(name), type(type), owner(owner) {}

Component::~Component()
{
    this->owner = NULL;
    this->type = NotSet;
}

void Component::attachOwner(GameObject* owner)
{
    this->owner = owner;
}

void Component::detachOwner()
{
    this->owner = NULL;
    delete this;
}

GameObject* Component::getOwner()
{
    return this->owner;
}

Component::ComponentType Component::getType()
{
    return this->type;
}

Component::String Component::getName()
{
    return this->name;
}
