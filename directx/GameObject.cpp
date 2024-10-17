#include "GameObject.h"
#include "EngineTime.h"

GameObject::GameObject(std::string name) : name(name) {
	std::cout << "Creating Game Object: " << name << std::endl;
	this->isActive = true;

	cc.time = 0;
	cc.world.setIdentity();
	cc.view.setIdentity();
	cc.proj.setIdentity();

	transform.position = Vector3(0);
	transform.rotation = Vector3(0);
	transform.scale = Vector3(1);

	cc.world.setTranslation(transform.position);
}

GameObject::GameObject(std::string name, OBJECT_TYPE type) :
	name(name), type(type) {
	this->isActive = true;

	cc.time = 0;
	cc.world.setIdentity();
	cc.view.setIdentity();
	cc.proj.setIdentity();

	transform.position = Vector3(0);
	transform.rotation = Vector3(0);
	transform.scale = Vector3(1);

	cc.world.setTranslation(transform.position);
}

GameObject::~GameObject() {}

void GameObject::update(float deltaTime, RECT viewport)
{
	this->cc.time = deltaTime;
}

void GameObject::draw()
{
}

void GameObject::translate(Vector3 offset, float speed)
{
	this->transform.position += offset * speed * (float)EngineTime::getDeltaTime();
	this->cc.world.setIdentity();
	this->cc.world.setTranslation(this->transform.position);
}

void GameObject::rotateX(float radians)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationX(radians);

	this->cc.world *= rotation;
}

void GameObject::rotateY(float radians)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationY(radians);

	this->cc.world *= rotation;
}

void GameObject::rotateZ(float radians)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationZ(radians);

	this->cc.world *= rotation;
}

void GameObject::scale(Vector3 offset)
{
	Matrix4x4 scale;
	scale.setIdentity();
	scale.setScale(transform.scale = Vector3::lerp(transform.scale, transform.scale + offset, (sin(this->cc.time) + 1.0f) / 2.0f));
	this->cc.world *= scale;
}

void GameObject::setPosition(Vector3 newPos)
{
	this->transform.position = newPos;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->transform.position = Vector3(x, y, z);
}

Vector3 GameObject::getPosition()
{
	return this->transform.position;
}

void GameObject::setRotation(Vector3 newRot)
{
	this->transform.rotation.x += newRot.x;
	this->transform.rotation.y += newRot.y;
	this->transform.rotation.z += newRot.z;
}

void GameObject::resetView()
{
	this->cc.view.setIdentity();
}

void GameObject::project(int type, RECT viewport)
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
