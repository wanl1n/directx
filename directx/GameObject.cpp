#include "GameObject.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "CameraManager.h"

GameObject::GameObject(std::string name, OBJECT_TYPE type) :
	name(name), type(type) {
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
	this->isActive = true;

	cc.time = 0;
	cc.world.setIdentity();
	cc.view.setIdentity();
	cc.proj.setIdentity();

	transform.position = Vector3(0);
	transform.rotation = Vector3(0);
	transform.scale = Vector3(1);

	cc.world.setTranslation(transform.position);
	
	this->calculateBounds();

	// Create Constant Buffer and load.
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(Constant));
}

GameObject::~GameObject() {}

void GameObject::calculateBounds()
{
	this->bounds = {
		-1 * transform.scale.x + transform.position.x, 1 * transform.scale.x + transform.position.x,
		-1 * transform.scale.y + transform.position.y, 1 * transform.scale.y + transform.position.y,
		-1 * transform.scale.z + transform.position.z, 1 * transform.scale.z + transform.position.z };
}

void GameObject::calculateWorldMatrix()
{
	this->cc.world.setIdentity();

	// Scale
	Matrix4x4 scale;
	scale.setIdentity();
	scale.setScale(this->transform.scale);

	// Rotation
	Matrix4x4 rotation;
	Matrix4x4 temp;

	rotation.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->transform.rotation.x);
	rotation *= temp;

	temp.setIdentity();
	temp.setRotationY(this->transform.rotation.y);
	rotation *= temp;

	temp.setIdentity();
	temp.setRotationZ(this->transform.rotation.z);
	rotation *= temp;

	// Translate
	Matrix4x4 translate;
	translate.setIdentity();
	translate.setTranslation(transform.position);

	this->cc.world *= scale;
	this->cc.world *= rotation;
	this->cc.world *= translate;
}

void GameObject::update(float deltaTime, RECT viewport)
{
	this->cc.time = deltaTime;

	if (isSelected)
		this->edit(deltaTime);

	this->calculateWorldMatrix();

	this->cc.view = CameraManager::getInstance()->getActiveCameraView();
	this->cc.proj = CameraManager::getInstance()->getActiveProjection();

	this->cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &this->cc);

	this->calculateBounds();
}

void GameObject::draw() {}

void GameObject::edit(float deltaTime)
{
	float step = 1.0f * deltaTime;
	if (InputSystem::getInstance()->isKeyDown('W'))
		this->transform.position.z += step;
	if (InputSystem::getInstance()->isKeyDown('A'))
		this->transform.position.x -= step;
	if (InputSystem::getInstance()->isKeyDown('S'))
		this->transform.position.z -= step;
	if (InputSystem::getInstance()->isKeyDown('D'))
		this->transform.position.x += step;

	if (InputSystem::getInstance()->isKeyDown('Q'))
		this->transform.position.y -= step;
	if (InputSystem::getInstance()->isKeyDown('E'))
		this->transform.position.y += step;

	//std::cout << "Editing " << name << std::endl;
}

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

std::string GameObject::getName()
{
	return this->name;
}

bool GameObject::getActive()
{
	return this->isActive;
}

// GETTERS AND SETTERS
Vector3 GameObject::getPosition()
{
	return this->transform.position;
}

Vector3 GameObject::getRotation()
{
	return this->transform.rotation;
}

Vector3 GameObject::getScale()
{
	return this->transform.scale;
}

void GameObject::setName(std::string name)
{
	this->name = name;
}

void GameObject::setActive(bool active)
{
	this->isActive = active;
}

bool GameObject::isWithinBounds(Vector3 ray)
{
	return (
		ray.x >= bounds.minX &&
		ray.x <= bounds.maxX &&
		ray.y >= bounds.minY &&
		ray.y <= bounds.maxY &&
		ray.z >= bounds.minZ &&
		ray.z <= bounds.maxZ
		);
}

void GameObject::setPosition(Vector3 newPos)
{
	this->transform.position = newPos;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->transform.position = Vector3(x, y, z);
}

void GameObject::setRotation(Vector3 newRot)
{
	this->transform.rotation.x = newRot.x;
	this->transform.rotation.y = newRot.y;
	this->transform.rotation.z = newRot.z;
}

void GameObject::setRotationX(float radians)
{
	this->transform.rotation.x = radians;
}

void GameObject::setRotationY(float radians)
{
	this->transform.rotation.y = radians;
}

void GameObject::setRotationZ(float radians)
{
	this->transform.rotation.z = radians;
}

void GameObject::setScale(Vector3 newScale)
{
	this->transform.scale = newScale;
}

void GameObject::setSelected(bool selected)
{
	this->isSelected = selected;
}
