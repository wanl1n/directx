#include "PhysicsPlane.h"
#include "InputSystem.h"
#include "PhysicsComponent.h"

PhysicsPlane::PhysicsPlane(std::string name, bool blending) :
	Cube(name, blending, PHYSICS_PLANE)
{
	this->frontColor = CORALROSE;
	this->backColor = ROSETAUPE;

	this->init();

	this->setPosition(Math::Vector3(0, -2.0f, 0));
	cc.world.setTranslation(transform.position);
	this->transform.scale = Math::Vector3(30.0f, 0.3f, 30.0f);

	PhysicsComponent* rb = new PhysicsComponent(name + " Rigidbody", this);
	this->attachComponent(rb);
	rb->getRigidBody()->setType(BodyType::KINEMATIC);
	this->physOn = true;
}

PhysicsPlane::~PhysicsPlane() {}

std::vector<Vertex3D> PhysicsPlane::createVertices()
{
	std::vector<Vertex3D> vecVerts;

	int size = 24;

	Math::Vector3 xyzs[] = {
		// FRONT FACE
		Math::Vector3(-side, -side, -side),
		Math::Vector3(-side, side, -side),
		Math::Vector3(side, side, -side),
		Math::Vector3(side, -side, -side),
		// BACK FACE
		Math::Vector3(side, -side, side),
		Math::Vector3(side, side, side),
		Math::Vector3(-side, side, side),
		Math::Vector3(-side, -side, side)
	};
	int posIndexList[] = { 0, 1, 2, 3,
							4, 5, 6, 7,
							1, 6, 5, 2,
							7, 0, 3, 4,
							3, 2, 5, 4,
							7, 6, 1, 0 };

	Vector4 rgbas_rb[] = { RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, PINK,
						   RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, PINK,
						   RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, PINK };
	Vector4 rgbas_wh[] = { frontColor, frontColor, frontColor, frontColor,
						   backColor, backColor, backColor, backColor,
						   frontColor, frontColor, frontColor, frontColor,
						   backColor, backColor, backColor, backColor,
						   frontColor, frontColor, frontColor, frontColor,
						   backColor, backColor, backColor, backColor };

	std::vector<Vector4> rgbas;
	for (int i = 0; i < size; i++) {
		if (COLOR_SETTINGS == RAINBOW_COLORED)
			rgbas.push_back(rgbas_rb[i]);
		else if (COLOR_SETTINGS == WHITE_COLORED)
			rgbas.push_back(rgbas_wh[i]);
	}

	Math::Vector2 uvs[] =
	{
		{ Math::Vector2(0.0f,0.0f) },
		{ Math::Vector2(0.0f,1.0f) },
		{ Math::Vector2(1.0f,0.0f) },
		{ Math::Vector2(1.0f,1.0f) }
	};
	int texIndexList[] = { 1, 0, 2, 3 };

	int indexCounter = 0;
	for (int i = 0; i < size; i++) {
		Vertex3D vert = { xyzs[posIndexList[i]], uvs[texIndexList[i % 4]], rgbas[i] };
		vecVerts.push_back(vert);
	}

	return vecVerts;
}

Math::Vector3 PhysicsPlane::getPosition()
{
	ComponentList physComponents = this->getComponentsOfType(Component::ComponentType::Physics);
	
	PhysicsComponent* physComp = (PhysicsComponent*)physComponents[0];
	if (physComp != NULL) {
		return physComp->getRBPosition();
	}

	return Math::Vector3(0);
}

Math::Vector3 PhysicsPlane::getRotation()
{
	ComponentList physComponents = this->getComponentsOfType(Component::ComponentType::Physics);

	PhysicsComponent* physComp = (PhysicsComponent*)physComponents[0];
	if (physComp != NULL) {
		return physComp->getRBRotation();
	}

	return Math::Vector3(0);
}
