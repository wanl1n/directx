#include "Plane.h"
#include "InputSystem.h"
#include "PhysicsComponent.h"

Plane::Plane(std::string name, bool blending, OBJECT_TYPE type) :
	Cube(name, blending, PLANE)
{
	this->frontColor = WHITE;
	this->backColor = ROSETAUPE;

	this->init();

	/*this->setPosition(0, -15, 0);
	cc.world.setTranslation(transform.position);
	this->transform.scale = Math::Vector3(30.0f, 1.0f, 30.0f);*/
}

Plane::~Plane() {}

std::vector<Vertex3D> Plane::createVertices()
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
