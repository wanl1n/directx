#pragma once
#include <string>
#include <d3d11.h>
#include "DirectXMath.h"

#include "GameObject.h"
#include "InputListener.h"
#include "Constants.h"

using namespace Math;

class CameraManager;

class Camera : public GameObject, public InputListener
{
	protected:
		Matrix4x4 prevCamMat;

		int type = 0;
		float forward = 0;
		float rightward = 0;
		float panSpeed = 0.1f;
		float moveSpeed = 1.0f;

		bool moving = false;
		bool updatedCameraProjPos = false;
		RECT viewport;

		GameObject* lastSelectedGO;

		friend class CameraManager;

		bool firstMouseDown = true;
		bool leftMouseDown = false;
		DirectX::XMVECTOR lastHitPos;
		DirectX::XMVECTOR deltaHitPos;

		bool firstRecord = true;

		Math::Vector2 oldMousePos;

	public:
		Camera(std::string name, RECT viewport, OBJECT_TYPE type = CAMERA);
		~Camera();

		virtual void update();
		virtual void checkForInput();
		virtual void updateViewMatrix();
		virtual void updateProjectionMatrix();

		float getPanSpeed();
		Matrix4x4 getViewMatrix();
		Matrix4x4 getProjMatrix();
		void setForward(float dir);
		void setRightward(float dir);
		void setProjectionType(int type);

		// Inherited from InputListener.
		void onMouseMove(const Math::Vector2& mousePos) override;
		void onLeftMouseDown(const Math::Vector2& mousePos) override;
		void onRightMouseDown(const Math::Vector2& mousePos) override;
		void onLeftMouseUp(const Math::Vector2& mousePos) override;
		void onRightMouseUp(const Math::Vector2& mousePos) override;
};

