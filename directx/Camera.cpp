#include "Camera.h"

Camera::Camera(std::string name, OBJECT_TYPE type) : GameObject(name, type)
{
	if (type == ORTHO_CAMERA)
		this->type = ORTHOGRAPHIC;
	else if (type == PERSPECTIVE_CAMERA)
		this->type = PERSPECTIVE;

	this->prevCamMat.setIdentity();
	this->prevCamMat.setTranslation(Vector3(0, 0, -6));
}

Camera::~Camera() {}

void Camera::update(RECT viewport)
{
	this->updateTransform();
	this->project(viewport);
}

void Camera::updateTransform()
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
	Vector3 newPos = prevCamMat.getTranslation() + worldCam.getZDir() * (this->forward * 0.3f);
	newPos += worldCam.getXDir() * (this->rightward * 0.3f);

	// Update Camera Rot and Translation
	worldCam.setTranslation(newPos);
	prevCamMat = worldCam;
	worldCam.inverse();
	viewMat = worldCam;
}

void Camera::project(RECT viewport)
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

Matrix4x4 Camera::getCameraView()
{
	return this->viewMat;
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