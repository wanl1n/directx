#include "PhysicsComponent.h"

#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "Vector3.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner)
    : Component(name, Component::ComponentType::Physics, owner)
{
    // Register to physics system.
    BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
    PhysicsCommon* common = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    PhysicsWorld* world = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

    Math::Vector3 scale = this->owner->getScale();
    Math::Vector3 pos = this->owner->getLocalPosition();

    reactphysics3d::Transform transform;
    transform.setFromOpenGL(this->owner->getPhysicsLocalMatrix());
    transform.setPosition(reactphysics3d::Vector3(pos.x, pos.y, pos.z));

    BoxShape* boxShape = common->createBoxShape(reactphysics3d::Vector3(scale.x, scale.y, scale.z));
    this->rb = world->createRigidBody(transform);
    this->rb->addCollider(boxShape, transform);
    this->rb->updateMassPropertiesFromColliders();
    this->rb->setMass(this->mass);
    this->rb->setType(BodyType::DYNAMIC);
    this->rb->setIsDebugEnabled(true);

    transform = this->rb->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->owner->setWorldMat(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
    Component::~Component();
    BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{
    const reactphysics3d::Transform transform = this->rb->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->owner->setWorldMat(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return this->rb;
}

Math::Vector3 PhysicsComponent::getRBPosition()
{
    const reactphysics3d::Transform transform = this->rb->getTransform();
    return Math::Vector3(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);
}

Math::Vector3 PhysicsComponent::getRBRotation()
{
    const reactphysics3d::Transform transform = this->rb->getTransform();
    return Math::Vector3(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z);

}
