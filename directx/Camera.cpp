#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(std::string name, OBJECT_TYPE type) : GameObject(name, type)
{
	if (type == ORTHO_CAMERA)
		this->type = ORTHOGRAPHIC;
	else if (type == PERSPECTIVE_CAMERA)
		this->type = PERSPECTIVE;

	this->prevCamMat.setIdentity();
	this->prevCamMat.setTranslation(Vector3(0, 0, -6));

	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera() {}

void Camera::update(RECT viewport)
{
	this->checkForInput();
	this->updateProjectionMatrix(viewport);
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
	Vector3 newPos = prevCamMat.getTranslation() + worldCam.getZDir() * (this->forward * moveSpeed);
	newPos += worldCam.getXDir() * (this->rightward * moveSpeed);

	// Update Camera Rot and Translation
	worldCam.setTranslation(newPos);
	prevCamMat = worldCam;
	worldCam.inverse();
	this->cc.view = worldCam;
}

void Camera::updateProjectionMatrix(RECT viewport)
{
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);

	switch (type) {
		case ORTHOGRAPHIC:
			this->cc.proj.setOrthoLH(
				width / 400.0f,
				height / 400.0f,
				-4.0f, 4.0f
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
		default:
			this->cc.proj.setOrthoLH(
				(viewport.right - viewport.left) / 400.0f,
				(viewport.bottom - viewport.top) / 400.0f,
				-4.0f, 4.0f
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

void Camera::onMouseMove(const Point& mousePos)
{
	/*RECT viewport = this->getClientWindowRect();
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);

	float speed = CameraManager::getInstance()->getActiveCamera()->getPanSpeed();
	float deltaRotX = (mousePos.y - (height / 2.0f)) * deltaTime * speed;
	float deltaRotY = (mousePos.x - (width / 2.0f)) * deltaTime * speed;

	InputSystem::getInstance()->setCursorPosition(Point(width / 2.0f, height / 2.0f));

	CameraManager::getInstance()->getActiveCamera()->setRotationX(deltaRotX);
	CameraManager::getInstance()->getActiveCamera()->setRotationY(deltaRotY);*/
}

void Camera::onLeftMouseDown(const Point& mousePos)
{
}

void Camera::onRightMouseDown(const Point& mousePos)
{
	moving = true;
}

void Camera::onLeftMouseUp(const Point& mousePos)
{
}

void Camera::onRightMouseUp(const Point& mousePos)
{
	moving = false;
}
