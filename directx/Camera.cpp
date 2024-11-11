#include "Camera.h"

// Singletons
#include "InputSystem.h"
#include "EngineTime.h"
#include "GameObjectManager.h"

Camera::Camera(std::string name, RECT viewport, OBJECT_TYPE type) :
	GameObject(name, type), viewport(viewport), lastSelectedGO(NULL), updatedCameraProjPos(false)
{
	if (type == ORTHO_CAMERA)
		this->type = ORTHOGRAPHIC;
	else if (type == PERSPECTIVE_CAMERA)
		this->type = PERSPECTIVE;

	this->transform.position = Vector3(0, 0, -3);
	this->prevCamMat.setIdentity();
	this->prevCamMat.setTranslation(this->transform.position);
	this->updateViewMatrix();
}

Camera::~Camera() {}

void Camera::update()
{
	this->checkForInput(); // View
	this->updateProjectionMatrix(); // Projection

	if (!updatedCameraProjPos) {
		if (this->type == TOPDOWN) {
			this->transform.position.y = 15.0f;
			this->transform.rotation.x = 1.57f;
		}

		if (this->type == SIDESCROLLER) {
			this->transform.position.y = 1.0f;
			this->transform.rotation = Vector3(0);
		}

		this->updatedCameraProjPos = true;
		this->updateViewMatrix();
	}

	GameObject::update(EngineTime::getDeltaTime(), viewport);
}

void Camera::checkForInput()
{
	if (InputSystem::getInstance()->isKeyDown('W'))
		this->forward = 1.0f;
	if (InputSystem::getInstance()->isKeyDown('A'))
		this->rightward = -1.0f;
	if (InputSystem::getInstance()->isKeyDown('S'))
		this->forward = -1.0f;
	if (InputSystem::getInstance()->isKeyDown('D'))
		this->rightward = 1.0f;

	if (InputSystem::getInstance()->isKeyUp('W') ||
		InputSystem::getInstance()->isKeyUp('S'))
		this->forward = 0.0f;
	if (InputSystem::getInstance()->isKeyUp('D') ||
		InputSystem::getInstance()->isKeyUp('A'))
		this->rightward = 0.0f;

	// Update if the camera is moving.
	if (moving)
		this->updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	Matrix4x4 temp;

	// Rotation
	worldCam.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->transform.rotation.x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->transform.rotation.y);
	worldCam *= temp;

	// Translation
	if (this->type < 2)
		this->transform.position = prevCamMat.getTranslation() + worldCam.getZDir() * (this->forward * moveSpeed);
	else
		this->transform.position = prevCamMat.getTranslation() + worldCam.getYDir() * (this->forward * moveSpeed);
	this->transform.position += worldCam.getXDir() * (this->rightward * moveSpeed);

	// Update Camera Rot and Translation
	worldCam.setTranslation(this->transform.position);
	prevCamMat = worldCam;
	worldCam.inverse();
	this->cc.view = worldCam;
}

void Camera::updateProjectionMatrix()
{
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);

	switch (type) {
		case ORTHOGRAPHIC:
			this->cc.proj.setOrthoLH(
				width / 100.0f,
				height / 100.0f,
				-100.0f, 100.0f
			);
			break;
		case PERSPECTIVE:
			this->cc.proj.setPerspectiveFovLH(
				1.57f, // fov
				(float)width / (float)height, // aspect
				0.1f, // near
				100.0f // far
			);
			break;
		case TOPDOWN:
			this->cc.proj.setOrthoLH(
				width / 100.0f,
				height / 100.0f,
				-100.0f, 100.0f
			);
			break;
		case SIDESCROLLER:
			this->cc.proj.setOrthoLH(
				width / 100.0f,
				height / 100.0f,
				-100.0f, 100.0f
			);
			break;
		default:
			this->cc.proj.setOrthoLH(
				width / 100.0f,
				height / 100.0f,
				-100.0f, 100.0f
			);
			break;
	}
}

float Camera::getPanSpeed()
{
	return this->panSpeed;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->cc.view;
}

Matrix4x4 Camera::getProjMatrix()
{
	return this->cc.proj;
}

void Camera::setForward(float dir)
{
	this->forward = dir;
}

void Camera::setRightward(float dir)
{
	this->rightward = dir;
}

void Camera::setProjectionType(int type)
{
	this->type = type;
	this->updatedCameraProjPos = false;
}

void Camera::onMouseMove(const Point& mousePos)
{
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);
	float deltaTime = EngineTime::getDeltaTime();

	if (moving && this->type < 2) {
		this->transform.rotation.x += (mousePos.y - (height / 2.0f)) * deltaTime * panSpeed;
		this->transform.rotation.y += (mousePos.x - (width / 2.0f)) * deltaTime * panSpeed;
		InputSystem::getInstance()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
	}

	if (leftMouseDown)
		GameObjectManager::getInstance()->transformSelectedGameObject(deltaHitPos);
}

void Camera::onLeftMouseDown(const Point& mousePos)
{
	leftMouseDown = true; 

	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);

	/*DirectX::XMVECTOR newHitPos = GameObjectManager::getInstance()->pick(mousePos, width, height);
	if (firstMouseDown) {
		firstMouseDown = false;
		this->lastHitPos = newHitPos;
		this->deltaHitPos = DirectX::XMVectorSet(0, 0, 0, 0);
	}
	else {
		this->deltaHitPos = DirectX::XMVectorSubtract(newHitPos, lastHitPos);
		this->lastHitPos = newHitPos;
	}*/
}

void Camera::onRightMouseDown(const Point& mousePos)
{
	moving = true;
}

void Camera::onLeftMouseUp(const Point& mousePos)
{
	leftMouseDown = false;
}

void Camera::onRightMouseUp(const Point& mousePos)
{
	moving = false;
}
