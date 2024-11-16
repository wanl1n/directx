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