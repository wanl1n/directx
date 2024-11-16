#include "Cube.h"

Cube::Cube(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, type, blending), side(1), frontColor(WHITE), backColor(WHITE)
{
	// Default Values
	this->side = 0.5f;
	this->size = Math::Vector3(side * 2);
	this->frontColor = WHITE;
	this->backColor = WHITE;

	this->init();

	this->cc.world.setScale(transform.scale);
	this->setPosition(Math::Vector3(0, 0, 0));
}

Cube::~Cube() {}

void Cube::initializeBuffers()
{
	unsigned int indices[] = {
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};
	UINT size_indices = ARRAYSIZE(indices);
	this->ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indices, size_indices);
}

std::vector<Vertex3D> Cube::createVertices()
{
	std::vector<Vertex3D> vecVerts;
	std::cout << "cube vertices" << std::endl;

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
			rgbas.push_back(WHITE);
		else
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

void Cube::calculateBounds()
{
	this->bounds = { 
		-side * transform.scale.x + transform.position.x, side * transform.scale.x + transform.position.x,
		-side * transform.scale.y + transform.position.y, side * transform.scale.y + transform.position.y,
		-side * transform.scale.z + transform.position.z, side * transform.scale.z + transform.position.z };
}

Math::Vector3 Cube::getPosition()
{
	return transform.position;
}

Math::Vector3 Cube::getRotation()
{
	return transform.rotation;
}
