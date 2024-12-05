#include "PhysicsSystem.h"

#include "EngineTime.h"
#include "PhysicsComponent.h"

PhysicsSystem::PhysicsSystem()
{
	// Create the physics engine and world.
	this->physicsCommon = new PhysicsCommon();

	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	/*settings.persistentContactDistanceThreshold = 0.01;
	settings.defaultFrictionCoefficient = 0.5f;*/
	settings.gravity = reactphysics3d::Vector3(0, -9.81f, 0);

	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
	//std::cout << "Successfully created physics world." << std::endl;
}

PhysicsSystem::~PhysicsSystem()
{
	delete this->physicsCommon;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->componentTable[component->getName()] = component;
	this->componentList.push_back(component);
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	if (this->componentTable[component->getName()] != NULL) {
		this->componentTable.erase(component->getName());
		 
		for (int i = 0; i < componentList.size(); i++) {
			if (component == componentList[i]) {
				this->componentList.erase(componentList.erase(componentList.begin() + i));
				i = componentList.size();
			}
		}
	}
}

void PhysicsSystem::unregisterComponentbyName(String name)
{
	if (this->componentTable[name] != NULL)
		this->unregisterComponent(this->componentTable[name]);
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
	return this->componentTable[name];
}

PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
	if (EngineTime::getDeltaTime() > 0) {
		this->physicsWorld->update(EngineTime::getDeltaTime());

		for (Component* comp : this->componentList) {
			comp->perform(EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}
