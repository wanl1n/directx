#pragma once
#include <iostream>
#include <string>
#include <d3d11.h>
#include "DirectXMath.h"
#include "SimpleMath/SimpleMath.h"

#include "Windows.h"
#include "GraphicsEngine.h"
#include "ConstantBuffer.h"

#include "Constants.h"
#include "Vertex.h"
#include "Math.h"
#include "Transform.h"
#include "Constants.h"

class GameObjectManager;

class GameObject
{
	protected:
		ConstantBufferPtr cb;

		std::string name;
		bool isActive;
		bool isSelected;
		OBJECT_TYPE type;

		Bounds bounds;
		DirectX::BoundingBox boundingBox;

		Constant cc;
		Transform transform;
		Vector3 size;

	private:
		friend class GameObjectManager;

	public:
		GameObject(std::string name, OBJECT_TYPE type);
		~GameObject();
		virtual void calculateBounds();
		virtual void calculateWorldMatrix();

		virtual void update(float deltaTime, RECT viewport);
		virtual void draw();

		// Editing Mode
		virtual void edit(float deltaTime);

		// Transform Functions
		virtual void translate(Vector3 offset, float speed);
		virtual void rotateX(float radians);
		virtual void rotateY(float radians);
		virtual void rotateZ(float radians);
		virtual void scale(Vector3 offset);
		virtual void resetView();

		// Getters/Setters
		virtual std::string getName();
		virtual bool getActive();
		virtual Vector3 getPosition();
		virtual Vector3 getRotation();
		virtual Vector3 getScale();
		virtual DirectX::BoundingBox getBounds();
		virtual Matrix4x4 getWorldMat();

		virtual void setName(std::string name);
		virtual void setActive(bool active);
		virtual bool isWithinBounds(Vector3 ray);
		virtual void setPosition(Vector3 newPos);
		virtual void setPosition(float x, float y, float z);
		virtual void setRotation(Vector3 newRot);
		virtual void setRotationX(float xOffset);
		virtual void setRotationY(float yOffset);
		virtual void setRotationZ(float zOffset);
		virtual void setScale(Vector3 newScale);
		virtual void setSelected(bool selected);
};

