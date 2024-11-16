#include "PhysicsCube.h"

#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(std::string name, bool blending) : 
	Cube(name, blending, PHYSICS_CUBE) 
{
	this->setPosition(Math::Vector3(0, 8, 0));
	cc.world.setTranslation(transform.position);
	cc.world.printMatrix();
	PhysicsComponent* rb = new PhysicsComponent(name + " Rigidbody", this);
	this->attachComponent(rb);
	this->physOn = true;
}

PhysicsCube::~PhysicsCube() {}

Math::Vector3 PhysicsCube::getPosition()
{
	ComponentList physComponents = this->getComponentsOfType(Component::ComponentType::Physics);

	PhysicsComponent* physComp = (PhysicsComponent*)physComponents[0];
	if (physComp != NULL) {
		return physComp->getRBPosition();
	}

	return Math::Vector3(0);
}

Math::Vector3 PhysicsCube::getRotation()
{
	ComponentList physComponents = this->getComponentsOfType(Component::ComponentType::Physics);

	PhysicsComponent* physComp = (PhysicsComponent*)physComponents[0];
	if (physComp != NULL) {
		return physComp->getRBRotation();
	}

	return Math::Vector3(0);
}