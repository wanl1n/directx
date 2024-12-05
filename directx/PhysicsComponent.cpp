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

    // Get Owner Properties
    Math::Vector3 scale = this->owner->getScale();
    Math::Vector3 pos = this->owner->getLocalPosition();
    Math::Vector3 rot = this->owner->getLocalRotation();

    // Create transform to save to the rigidbody.
    reactphysics3d::Transform transform;
    //transform.setPosition(reactphysics3d::Vector3(0, 0, 0));
    transform.setPosition(reactphysics3d::Vector3(pos.x, pos.y, pos.z));
    transform.setOrientation(Quaternion::fromEulerAngles(rot.x, rot.y, rot.z));

    // Create collider.
    BoxShape* boxShape = common->createBoxShape(reactphysics3d::Vector3(scale.x, scale.y, scale.z));
    
    // Create rigidbody.
    this->rb = world->createRigidBody(transform);
    this->rb->addCollider(boxShape, transform);
    this->rb->updateMassPropertiesFromColliders();
    this->rb->setMass(this->mass);
    this->rb->setType(BodyType::DYNAMIC);

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

std::string PhysicsComponent::getRBType()
{
    switch (this->rb->getType()) {
        case BodyType::STATIC:
            return "Static";
            break;
        case BodyType::DYNAMIC:
            return "Dynamic";
            break;
        case BodyType::KINEMATIC:
            return "Kinematic";
            break;
        default:
            return "";
            break;
    }
    return "";
}

float PhysicsComponent::getMass()
{
    return this->mass;
}

bool PhysicsComponent::isGravityOn()
{
    return this->rb->isGravityEnabled();
}

void PhysicsComponent::setMass(float mass)
{
    if (this->mass != mass)
        this->resetVelocity();

    this->mass = mass;
    this->rb->setMass(this->mass);
}

void PhysicsComponent::setGravityOn(bool grav)
{
    if (this->rb->isGravityEnabled() != grav)
        this->resetVelocity();

    this->rb->enableGravity(grav);
}

void PhysicsComponent::setRBType(std::string type)
{
    // If body type is going to change, reset force and torque.
    if (this->getRBType() != type) 
        this->resetVelocity();

    if (type == "Static") 
        this->rb->setType(BodyType::STATIC);
    if (type == "Dynamic")
        this->rb->setType(BodyType::DYNAMIC);
    if (type == "Kinematic")
        this->rb->setType(BodyType::KINEMATIC);
}

void PhysicsComponent::setPositionLock(bool x, bool y, bool z)
{
    reactphysics3d::Vector3 oldLock = this->rb->getLinearLockAxisFactor();
    reactphysics3d::Vector3 newLock = reactphysics3d::Vector3(!x, !y, !z);
    if (oldLock != newLock) this->resetVelocity();

    this->rb->setLinearLockAxisFactor(newLock);
}

void PhysicsComponent::setRotationLock(bool x, bool y, bool z)
{
    reactphysics3d::Vector3 oldLock = this->rb->getAngularLockAxisFactor();
    reactphysics3d::Vector3 newLock = reactphysics3d::Vector3(!x, !y, !z);
    if (oldLock != newLock) this->resetVelocity();

    this->rb->setAngularLockAxisFactor(newLock);
}

void PhysicsComponent::resetVelocity()
{
    this->rb->setLinearVelocity(reactphysics3d::Vector3(0, 0, 0));
    this->rb->setAngularVelocity(reactphysics3d::Vector3(0, 0, 0));
}

