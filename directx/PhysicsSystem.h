#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent;

class PhysicsSystem
{
	public:
		typedef std::string String;
		typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
		typedef std::vector<PhysicsComponent*> ComponentList;

	private:
		ComponentTable componentTable;
		ComponentList componentList;

		PhysicsCommon* physicsCommon;
		PhysicsWorld* physicsWorld;

	public:
		PhysicsSystem();
		~PhysicsSystem();

		void registerComponent(PhysicsComponent* component);
		void unregisterComponent(PhysicsComponent* component);
		void unregisterComponentbyName(String name);
		PhysicsComponent* findComponentByName(String name);
		ComponentList getAllComponents();

		void updateAllComponents();
		PhysicsWorld* getPhysicsWorld();
		PhysicsCommon* getPhysicsCommon();
};

