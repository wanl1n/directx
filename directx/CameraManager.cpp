#include "CameraManager.h"
#include "Camera.h"

CameraManager* CameraManager::sharedInstance = nullptr;
CameraManager* CameraManager::getInstance()
{
	return sharedInstance;
}

void CameraManager::initialize()
{
	sharedInstance = new CameraManager();
}

CameraManager::CameraManager() : selectedCameraIndex(0) 
{
	// Default Camera.
	this->addCamera(PERSPECTIVE_CAMERA, 1);
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

void CameraManager::addCamera(OBJECT_TYPE type, int count)
{
	for (int i = 0; i < count; i++) {
		Camera* newCam = new Camera("Camera " + std::to_string(this->CameraList.size() + 1), type);
		this->CameraList.push_back(newCam);
	}
}

void CameraManager::removeCamera(Camera* cam)
{
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
	return this->CameraList[selectedCameraIndex]->getCameraView();
}

Matrix4x4 CameraManager::getActiveProjection()
{
	return this->CameraList[selectedCameraIndex]->getProjMatrix();
}

void CameraManager::setSelectedCameraIndex(int select)
{
	this->selectedCameraIndex = select;
}
