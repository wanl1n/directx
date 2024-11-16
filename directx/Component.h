#pragma once
#include <string>

class GameObject;

class Component
{
	public:
		typedef std::string String;
		enum ComponentType { NotSet = -1,
							 Script,
							 Renderer,
							 Input,
							 Physics };

	protected:
		GameObject* owner;
		ComponentType type;
		String name;

	public:
		Component(String name, ComponentType type, GameObject* owner);
		~Component();

		void attachOwner(GameObject* owner);
		void detachOwner();
		GameObject* getOwner();
		ComponentType getType();
		String getName();

		virtual void perform(float deltaTime) = 0;
};

