#include "GameObject.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "CameraManager.h"

GameObject::GameObject(std::string name, OBJECT_TYPE type) :
	name(name), type(type) 
{
	this->isActive = true;
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	cc.world.setIdentity();
	cc.view.setIdentity();
	cc.proj.setIdentity();

	transform.position = Math::Vector3(0);
	transform.rotation = Math::Vector3(0);
	transform.scale = Math::Vector3(1);
	transform.orientation = { 0, 0, 0, 0 };
	size = Math::Vector3(0.5f);

	cc.world.setTranslation(transform.position);
	
	this->calculateBounds();

	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(Constant));
}

GameObject::~GameObject() 
{
	for (Component* comp : components) {
		comp->detachOwner();
	}

	this->components.clear();
}

void GameObject::calculateBounds()
{
	this->bounds = {
		-0.5f * transform.scale.x + transform.position.x, 0.5f * transform.scale.x + transform.position.x,
		-0.5f * transform.scale.y + transform.position.y, 0.5f * transform.scale.y + transform.position.y,
		-0.5f * transform.scale.z + transform.position.z, 0.5f * transform.scale.z + transform.position.z };

	DirectX::XMFLOAT3 center = DirectX::XMFLOAT3(transform.position.x, transform.position.y, transform.position.z);
	DirectX::XMFLOAT3 sizeVec = DirectX::XMFLOAT3(size.x, size.y, size.z);
	this->boundingBox = { center, sizeVec };
}

void GameObject::calculateWorldMatrix()
{
	//std::cout << name << " calcWorldMatrix(): Begin." << std::endl;
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

	//std::cout << name << " calcWorldMatrix(): Scaling." << std::endl;
	this->cc.world *= scale;
	//std::cout << name << " calcWorldMatrix(): Rotating." << std::endl;
	this->cc.world *= rotation;
	//std::cout << name << " calcWorldMatrix(): Translating." << std::endl;
	this->cc.world *= translate;
}

void GameObject::awake()
{
}

void GameObject::update(float deltaTime, RECT viewport)
{
	this->cc.cameraPos = CameraManager::getInstance()->getActiveCamera()->getPosition();
	
	/*if (isSelected)
		this->edit(deltaTime);*/
	
	if (!physOn)
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

void GameObject::translate(Math::Vector3 offset, float speed)
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

void GameObject::scale(Math::Vector3 offset)
{
	Matrix4x4 scale;
	this->transform.scale += offset;
	scale.setIdentity();
	scale.setScale(transform.scale = Math::Vector3::lerp(transform.scale, transform.scale + offset, (sin(EngineTime::getDeltaTime()) + 1.0f) / 2.0f));
	this->cc.world *= scale;
}

void GameObject::attachComponent(Component* comp)
{
	this->components.push_back(comp);
	comp->attachOwner(this);
}

void GameObject::detachComponent(Component* comp)
{
	for (int i = 0; i < components.size(); i++) {
		if (comp == components[i])
			components.erase(components.begin() + i);
	}
}

Component* GameObject::findComponentByName(GameObject::String name)
{
	Component* comp = nullptr;

	for (Component* component : components) {
		if (component->getName() == name)
			comp = component;
	}

	return comp;
}

Component* GameObject::findComponentByType(Component::ComponentType type, GameObject::String name)
{
	Component* comp = nullptr;

	for (Component* component : components) {
		if (component->getName() == name && component->getType() == type)
			comp = component;
	}

	return comp;
}

GameObject::ComponentList GameObject::getAllComponents()
{
	return this->components;
}

GameObject::ComponentList GameObject::getComponentsOfType(Component::ComponentType type)
{
	GameObject::ComponentList objects;

	for (Component* component : components) {
		if (component->getType() == type)
			objects.push_back(component);
	}

	return objects;
}

float* GameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 openGLMat;
	openGLMat.setMatrix(cc.world);
	return openGLMat.getMatrixPointer();
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
Math::Vector3 GameObject::getPosition()
{
	return this->transform.position;
}

Math::Vector3 GameObject::getRotation()
{
	//return Math::Vector3(this->orientation.x, this->orientation.y, this->orientation.z);
	return this->transform.rotation;
}

Math::Vector3 GameObject::getScale()
{
	return this->transform.scale;
}

DirectX::BoundingBox GameObject::getBounds()
{
	return this->boundingBox;
}

Matrix4x4 GameObject::getWorldMat()
{
	return cc.world;
}

void GameObject::setName(std::string name)
{
	this->name = name;
}

void GameObject::setActive(bool active)
{
	this->isActive = active;
}

bool GameObject::isWithinBounds(Math::Vector3 ray)
{
	return (
		ray.x >= bounds.minX &&
		ray.x <= bounds.maxX &&
		ray.y >= bounds.minY &&
		ray.y <= bounds.maxY /* &&
		ray.z >= bounds.minZ &&
		ray.z <= bounds.maxZ*/
		);
}

void GameObject::setWorldMat(float matrix[16])
{
	Matrix4x4 physMat;
	physMat.setIdentity();

	int index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			physMat.mat[i][j] = matrix[index];
			index++;
		}
	}

	cc.world = physMat;

	/**/std::cout << name << " setWorldMat(), Physics: " << physOn << std::endl;

	Matrix4x4 newMatrix; 
	newMatrix.setMatrix(physMat);

	Matrix4x4 scaleMatrix; 
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(transform.scale);

	Matrix4x4 transMatrix; 
	transMatrix.setIdentity();
	transMatrix.setTranslation(transform.position);

	transMatrix *= newMatrix;
	scaleMatrix *= transMatrix;
	cc.world.setMatrix(scaleMatrix);
}

void GameObject::setPosition(Math::Vector3 newPos)
{
	this->transform.position = newPos;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->transform.position = Math::Vector3(x, y, z);
}

void GameObject::setRotation(Math::Vector3 newRot)
{
	this->transform.rotation.x = newRot.x;
	this->transform.rotation.y = newRot.y;
	this->transform.rotation.z = newRot.z;

	this->orientation = {};
	this->orientation.x = newRot.x;
	this->orientation.y = newRot.y;
	this->orientation.z = newRot.z;
}

void GameObject::setRotation(Math::Vector4 newRot)
{
	this->transform.rotation.x = newRot.x;
	this->transform.rotation.y = newRot.y;
	this->transform.rotation.z = newRot.z;

	this->orientation = {};
	this->orientation.x = newRot.x;
	this->orientation.y = newRot.y;
	this->orientation.z = newRot.z;
	this->orientation.w = newRot.w;
}

void GameObject::setRotationX(float radians)
{
	this->transform.rotation.x = radians;
	this->orientation.x = radians;
}

void GameObject::setRotationY(float radians)
{
	this->transform.rotation.y = radians;
	this->orientation.y = radians;
}

void GameObject::setRotationZ(float radians)
{
	this->transform.rotation.z = radians;
	this->orientation.z = radians;
}

void GameObject::setScale(Math::Vector3 newScale)
{
	this->transform.scale = newScale;
}

void GameObject::setSelected(bool selected)
{
	this->isSelected = selected;
}
