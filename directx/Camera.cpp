#include "Camera.h"

Camera::Camera(std::string name, OBJECT_TYPE type) : GameObject(name, type)
{
	Matrix4x4 temp;

	this->viewMat.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->transform.rotation.x);
	this->viewMat *= temp;

	temp.setIdentity();
	temp.setRotationY(this->transform.rotation.y);
	this->viewMat *= temp;

	this->viewMat.setTranslation(Vector3(0, 0, -2));
	this->viewMat.inverse();
}

Camera::~Camera() {}

Matrix4x4 Camera::getCameraView()
{
	return this->viewMat;
}
