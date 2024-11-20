#pragma once
#include <iostream>
#include <string>
#include <d3d11.h>
#include "DirectXMath.h"
#include "reactphysics3d/reactphysics3d.h"

#include "GraphicsEngine.h"
#include "ConstantBuffer.h"

#include "Constants.h"
#include "Vertex.h"
#include "Math.h"
#include "Transform.h"
#include "Constants.h"

#include "Component.h"

using namespace Math;
using namespace reactphysics3d;

class GameObjectManager;

class GameObject
{
	public:
		typedef std::string String;
		typedef std::vector<Component*> ComponentList;

	protected:
		ConstantBufferPtr cb;

		std::string name;
		bool isActive;
		OBJECT_TYPE type;

		Bounds bounds;

		Constant cc;
		Math::Vector3 size;

		bool isSelected;
		Struct::Transform transform;
		Quaternion orientation;

		float deltaTime;

		ComponentList components;
	public:
		bool physOn;

	private:
		friend class GameObjectManager;

	public:
		GameObject(std::string name, OBJECT_TYPE type);
		~GameObject();
		virtual void calculateBounds();
		virtual void calculateWorldMatrix();

		virtual void awake();
		virtual void update(float deltaTime, RECT viewport);
		virtual void draw();

		// Editing Mode
		virtual void edit(float deltaTime);

		// Transform Functions
		virtual void translate(Math::Vector3 offset, float speed);
		virtual void rotateX(float radians);
		virtual void rotateY(float radians);
		virtual void rotateZ(float radians);
		virtual void scale(Math::Vector3 offset);

		// Entity Component System
		void attachComponent(Component* comp);
		void detachComponent(Component* comp);

		// Getters/Setters
		virtual std::string getName();
		virtual std::string getTypeString();
		virtual bool getActive();
		virtual Math::Vector3 getLocalPosition();
		virtual Math::Vector3 getPosition();
		virtual Math::Vector3 getLocalRotation();
		virtual Math::Vector3 getRotation();
		virtual Math::Vector3 getScale();
		virtual bool isWithinBounds(Math::Vector3 ray);
		float* getPhysicsLocalMatrix();
		virtual Matrix4x4 getWorldMat();

		Component* findComponentByName(String name);
		Component* findComponentByType(Component::ComponentType type, String name);
		ComponentList getAllComponents();
		ComponentList getComponentsOfType(Component::ComponentType type);

		virtual void setName(std::string name);
		virtual void setActive(bool active);
		virtual void setWorldMat(float matrix[16]);
		virtual void setPosition(Math::Vector3 newPos);
		virtual void setPosition(float x, float y, float z);
		virtual void setRotation(Math::Vector3 newRot);
		virtual void setRotation(Math::Vector4 newRot);
		virtual void setRotationX(float xOffset);
		virtual void setRotationY(float yOffset);
		virtual void setRotationZ(float zOffset);
		virtual void setScale(Math::Vector3 newScale);
		virtual void setSelected(bool selected);
};

