#include "Camera.h"

// Singletons
#include "InputSystem.h"
#include "EngineTime.h"
#include "GameObjectManager.h"

Camera::Camera(std::string name, RECT viewport, OBJECT_TYPE type) : 
	GameObject(name, type), viewport(viewport), lastSelectedGO(NULL)
{
	if (type == ORTHO_CAMERA)
		this->type = ORTHOGRAPHIC;
	else if (type == PERSPECTIVE_CAMERA)
		this->type = PERSPECTIVE;

	// Test Case 6
	/*this->transform.position = Vector3(5.88311f, 2.36871f, -5.28797f);
	this->transform.rotation = Vector3(0.221113f, -0.802211f, 0);*/

	this->transform.position = Vector3(0, 0, -5);
	this->prevCamMat.setIdentity();
	this->prevCamMat.setTranslation(this->transform.position);
	this->updateViewMatrix();
}

Camera::~Camera() {}

void Camera::update()
{
	this->checkForInput();
	this->updateProjectionMatrix();

	//std::cout << "Camera Position: " << transform.position.x << ", " << this->transform.position.y << ", " << this->transform.position.z << std::endl;
	//std::cout << "Camera Rotation: " << this->transform.rotation.x << ", " << this->transform.rotation.y << std::endl;
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

	if (InputSystem::getInstance()->isKeyDown('O'))
		this->setProjectionType(ORTHOGRAPHIC);
	if (InputSystem::getInstance()->isKeyDown('P'))
		this->setProjectionType(PERSPECTIVE);

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
	this->transform.position = prevCamMat.getTranslation() + worldCam.getZDir() * (this->forward * moveSpeed);
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
}

void Camera::onMouseMove(const Point& mousePos)
{
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);
	float deltaTime = EngineTime::getDeltaTime();

	if (moving) {
		this->transform.rotation.x += (mousePos.y - (height / 2.0f)) * deltaTime * panSpeed;
		this->transform.rotation.y += (mousePos.x - (width / 2.0f)) * deltaTime * panSpeed;
		InputSystem::getInstance()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
	}
}

void Camera::onLeftMouseDown(const Point& mousePos)
{
	// 1. Get Screen point.
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);
	Vector3 screenPoint = Vector3(mousePos.x, mousePos.y, 1.0f);

	// 2. Convert screen point to world space.
	Vector4 worldPos = Matrix4x4::unproject(screenPoint, cc.view, cc.proj, width, height);
	Vector3 collPoint = Vector3(worldPos.x, worldPos.y, worldPos.z);
	
	// 3. Check if point collides with a GameObject.
	GameObject* selectedGO = GameObjectManager::getInstance()->checkCollision(collPoint);
	if (selectedGO != NULL)
		selectedGO->setSelected(true);
	else {
		if (lastSelectedGO != NULL) {
			lastSelectedGO->setSelected(false);
			lastSelectedGO = NULL;
		}
	}
	std::cout << "Ray Point: " << collPoint.x << ", " << collPoint.y << ", " << collPoint.z << std::endl;
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
