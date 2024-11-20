#pragma once
#include <string>

class PhysicsSystem;

class BaseComponentSystem
{
	public:
		typedef std::string String;

	private:
		PhysicsSystem* physicsSystem = nullptr;

	public:
		static BaseComponentSystem* getInstance();
		static void initialize();
		static void destroy();

		PhysicsSystem* getPhysicsSystem();

	private:
		BaseComponentSystem();
		~BaseComponentSystem();
		BaseComponentSystem(BaseComponentSystem const&) {};
		BaseComponentSystem& operator = (BaseComponentSystem const&) {};
		static BaseComponentSystem* sharedInstance;
};

