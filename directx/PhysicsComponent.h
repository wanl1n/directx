#pragma once
#include <string>
#include "Component.h"
#include "Math.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public Component
{
	private:
		float mass = 1000.0; //KG
		reactphysics3d::Vector3 gravity = reactphysics3d::Vector3(0, -9.81, 0);

		RigidBody* rb;

	public:
		PhysicsComponent(String name, GameObject* owner);
		~PhysicsComponent();

		void perform(float deltaTime) override;
		RigidBody* getRigidBody();

		Math::Vector3 getRBPosition();
		Math::Vector3 getRBRotation();
		std::string getRBType();
		float getMass();
		bool isGravityOn();
		
		void setMass(float mass);
		void setGravityOn(bool grav);
		void setRBType(std::string type);
		void setPositionLock(bool x, bool y, bool z);
		void setRotationLock(bool x, bool y, bool z);
		void resetVelocity();
};

