#include "GameObject.h"
#include "EngineTime.h"

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

void GameObject::draw() {}

void GameObject::translate(Vector3 offset, float speed)
{
	this->transform.position += offset * speed * (float)EngineTime::getDeltaTime();
	Matrix4x4 newPos;
	newPos.setIdentity();
	newPos.setTranslation(this->transform.position);

	this->cc.world *= newPos;
}

void GameObject::rotateX(float xOffset)
{
	this->transform.rotation.x += xOffset;

	this->setRotationX(this->transform.rotation.x);
}

void GameObject::rotateY(float yOffset)
{
	this->transform.rotation.y += yOffset;
	this->setRotationY(this->transform.rotation.y);
}

void GameObject::rotateZ(float zOffset)
{
	this->transform.rotation.z += zOffset;
	this->setRotationZ(this->transform.rotation.z);
}

void GameObject::scale(Vector3 offset)
{
	Matrix4x4 scale;
	this->transform.scale += offset;
	scale.setIdentity();
	scale.setScale(transform.scale = Vector3::lerp(transform.scale, transform.scale + offset, (sin(this->cc.time) + 1.0f) / 2.0f));
	this->cc.world *= scale;
}

void GameObject::resetView()
{
	this->cc.view.setIdentity();
}

// GETTERS AND SETTERS
Vector3 GameObject::getPosition()
{
	return this->transform.position;
}

void GameObject::setPosition(Vector3 newPos)
{
	this->transform.position = newPos;
	Matrix4x4 newPosMat;
	newPosMat.setIdentity();
	newPosMat.setTranslation(this->transform.position);

	this->cc.world *= newPosMat;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->transform.position = Vector3(x, y, z);
	this->cc.world.setIdentity();
	this->cc.world.setTranslation(this->transform.position);
}

void GameObject::setRotation(Vector3 newRot)
{
	this->transform.rotation.x = newRot.x;
	this->transform.rotation.y = newRot.y;
	this->transform.rotation.z = newRot.z;

	Matrix4x4 newRotMat;
	Matrix4x4 temp;

	// Rotation
	newRotMat.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->transform.rotation.x);
	newRotMat *= temp;

	temp.setIdentity();
	temp.setRotationY(this->transform.rotation.y);
	newRotMat *= temp;

	temp.setIdentity();
	temp.setRotationZ(this->transform.rotation.z);
	newRotMat *= temp;

	this->cc.world *= newRotMat;
}

void GameObject::setRotationX(float radians)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationX(radians);

	this->cc.world *= rotation;
}

void GameObject::setRotationY(float radians)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationY(radians);

	this->cc.world *= rotation;
}

void GameObject::setRotationZ(float radians)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationZ(radians);

	this->cc.world *= rotation;
}

void GameObject::setScale(Vector3 newScale)
{
	this->transform.scale = newScale;

	this->cc.world.setScale(this->transform.scale);
	/*Matrix4x4 scale;
	scale.setIdentity();
	scale.setScale(this->transform.scale);

	this->cc.world *= scale;*/
}
