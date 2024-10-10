#include "GameObject.h"

GameObject::GameObject(std::string name) : m_name(name) {
	cc.m_time = 0;
	cc.m_world.setIdentity();
	cc.m_view.setIdentity();
	cc.m_proj.setIdentity();

	transform.position = Vector3(0);
	transform.rotation = Vector3(0);
	transform.scale = Vector3(1);
}

GameObject::~GameObject() {}

void GameObject::update(float deltaTime)
{
	m_time += 1.57f * deltaTime;
	this->cc.m_time = m_time;
	//cc.m_time = ::GetTickCount64();

	this->deltaPos = deltaTime / 5000000;

	this->deltaScale += deltaTime / 0.15f;
	this->deltaRot += deltaTime / 0.55f;
}

void GameObject::translate(Vector3 offset)
{
	Matrix4x4 translation;
	Vector3 lerpValue;
	translation.setTranslation(lerpValue = Vector3::lerp(transform.position, transform.position + offset, this->deltaPos));

	this->transform.position += lerpValue;

	this->cc.m_world *= translation;
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
	// Offset Scaling.
	/*Matrix4x4 scale;
	scale.setScale(transform.scale = Vector3::lerp(transform.scale, transform.scale + offset, (sin(this->deltaScale) + 1.0f) / 2.0f));
	this->cc.m_world *= scale;*/

	// PULSING ANIMATION
	cc.m_world.setScale(Vector3::lerp(Vector3(0.5f, 0.5f, 0), Vector3(1, 1, 0), (sin(this->deltaScale) + 1.0f) / 2.0f));
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
