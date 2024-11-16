#pragma once
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public Component
{
	private:
		float mass = 1000.0f; //KG
		RigidBody* rb;

	public:
		PhysicsComponent(String name, GameObject* owner);
		~PhysicsComponent();

		void perform(float deltaTime) override;
		void updateOwnerTransform();
		RigidBody* getRigidBody();
};

