#include "CameraManager.h"
#include "Camera.h"
#include "InputSystem.h"

CameraManager* CameraManager::sharedInstance = nullptr;
CameraManager* CameraManager::getInstance()
{
	return sharedInstance;
}

void CameraManager::initialize(RECT viewport)
{
	sharedInstance = new CameraManager(viewport);
}

void CameraManager::destroy()
{
	if (sharedInstance == NULL)
		return;
	delete sharedInstance;
}

CameraManager::CameraManager(RECT viewport) : selectedCameraIndex(0)
{
	// Default Camera.
	this->addCamera(PERSPECTIVE_CAMERA, viewport, 1);
}

CameraManager::~CameraManager()
{
	this->CameraList.clear();
}

void CameraManager::update(RECT viewport)
{
	for (Camera* cam : this->CameraList)
	{
		if (cam->isActive)
			cam->update(viewport);
	}
}

void CameraManager::addCamera(OBJECT_TYPE type, RECT viewport, int count)
{
	for (int i = 0; i < count; i++) {
		Camera* newCam = new Camera("Camera " + std::to_string(this->CameraList.size() + 1), viewport, type);
		this->CameraList.push_back(newCam);
		InputSystem::getInstance()->addListener(newCam);
	}
}

void CameraManager::removeCamera(Camera* cam)
{
	InputSystem::getInstance()->removeListener(cam);

	std::vector<Camera*>::iterator it;

	for (it = this->CameraList.begin(); it != this->CameraList.end(); ++it) {
		if (*it == cam)
			this->CameraList.erase(it);
	}
}

Camera* CameraManager::getActiveCamera()
{
	return this->CameraList[selectedCameraIndex];
}

Matrix4x4 CameraManager::getActiveCameraView()
{
	return this->CameraList[selectedCameraIndex]->getViewMatrix();
}

Matrix4x4 CameraManager::getActiveProjection()
{
	return this->CameraList[selectedCameraIndex]->getProjMatrix();
}

void CameraManager::setSelectedCameraIndex(int select)
{
	this->selectedCameraIndex = select;
}
