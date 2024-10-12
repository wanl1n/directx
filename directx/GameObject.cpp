#include "GameObject.h"
#include "EngineTime.h"

GameObject::GameObject(std::string name) : m_name(name) {
	this->isActive = true;

	cc.m_time = 0;
	cc.m_world.setIdentity();
	cc.m_view.setIdentity();
	cc.m_proj.setIdentity();

	transform.position = Vector3(0);
	transform.rotation = Vector3(0);
	transform.scale = Vector3(1);

	cc.m_world.setTranslation(transform.position);
}

GameObject::GameObject(std::string name, PRIMITIVE type) : 
	m_name(name), type(type) {
	this->isActive = true;

	cc.m_time = 0;
	cc.m_world.setIdentity();
	cc.m_view.setIdentity();
	cc.m_proj.setIdentity();

	transform.position = Vector3(0);
	transform.rotation = Vector3(0);
	transform.scale = Vector3(1);

	cc.m_world.setTranslation(transform.position);
}

GameObject::~GameObject() {}

void GameObject::update(float deltaTime, RECT viewport)
{
	this->cc.m_time = deltaTime;
}

void GameObject::draw()
{
}

void GameObject::translate(Vector3 offset, float speed)
{
	this->transform.position += offset * speed * (float)EngineTime::getDeltaTime();
	this->cc.m_world.setTranslation(this->transform.position);
}

void GameObject::rotateX(float offset)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationX(offset);

	this->cc.m_world *= rotation;
}

void GameObject::rotateY(float offset)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationY(offset);

	this->cc.m_world *= rotation;
}

void GameObject::rotateZ(float offset)
{
	Matrix4x4 rotation;
	rotation.setIdentity();
	rotation.setRotationZ(offset);

	this->cc.m_world *= rotation;
}

void GameObject::scale(Vector3 offset)
{
	Matrix4x4 scale;
	scale.setScale(transform.scale = Vector3::lerp(transform.scale, transform.scale + offset, (sin(this->cc.m_time) + 1.0f) / 2.0f));
	this->cc.m_world *= scale;
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

void GameObject::resetView()
{
	cc.m_view.setIdentity();
}

void GameObject::project(int type, RECT viewport)
{
	switch (type) {
		case ORTHOGRAPHIC:
			this->cc.m_proj.setOrthoLH(
				(viewport.right - viewport.left) / 400.0f,
				(viewport.bottom - viewport.top) / 400.0f,
				-4.0f, 4.0f
			);
			break;
	}
}
