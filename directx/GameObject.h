#pragma once
#include <iostream>
#include <string>

class GameObject
{
	protected:
		std::string m_name;

	public:
		GameObject(std::string name);
		~GameObject();

		virtual bool release() = 0;
};

