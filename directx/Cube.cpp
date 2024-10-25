#include "Cube.h"

Cube::Cube(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, type, blending), side(1), frontColor(WHITE), backColor(WHITE)
{
	// Default Values
	this->side = 0.5f;
	this->frontColor = WHITE;
	this->backColor = WHITE;

	this->init();

	this->cc.world.setScale(Vector3(1));
	this->setPosition(Vector3(0, 1, 0));
}

Cube::~Cube() {}

void Cube::initializeBuffers()
{
	// Set up the Index buffer.
	unsigned int indices[] = {
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
	UINT size_indices = ARRAYSIZE(indices);
	this->ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indices, size_indices);
}

std::vector<Vertex3D> Cube::createVertices()
{
	std::vector<Vertex3D> vecVerts;

	if (COLOR_SETTINGS == RAINBOW_COLORED) {
		// 1. Set up the Vertex buffer.
		Vertex3D vertices[] = { // Cube Vertices
			// FRONT FACE
			{ Vector3(-side, -side, -side), RED },
			{ Vector3(-side, side, -side),	ORANGE },
			{ Vector3(side, side, -side),	YELLOW },
			{ Vector3(side, -side, -side),	GREEN },
			// BACK FACE
			{ Vector3(side, -side, side),	BLUE },
			{ Vector3(side, side, side),	INDIGO },
			{ Vector3(-side, side, side),	VIOLET },
			{ Vector3(-side, -side, side),	PINK }
		};
		UINT size_list = ARRAYSIZE(vertices);

		for (int i = 0; i < size_list; i++) {
			vecVerts.push_back(vertices[i]);
		}
	}
	else if (COLOR_SETTINGS == WHITE_COLORED) {
		// 1. Set up the Vertex buffer.
		Vertex3D vertices[] = { // Cube Vertices
			// FRONT FACE
			{ Vector3(-side, -side, -side), frontColor },
			{ Vector3(-side, side, -side),	frontColor },
			{ Vector3(side, side, -side),	frontColor },
			{ Vector3(side, -side, -side),	frontColor },
			// BACK FACE
			{ Vector3(side, -side, side),	backColor },
			{ Vector3(side, side, side),	backColor },
			{ Vector3(-side, side, side),	backColor },
			{ Vector3(-side, -side, side),	backColor }
		};
		UINT size_list = ARRAYSIZE(vertices);

		for (int i = 0; i < size_list; i++) {
			vecVerts.push_back(vertices[i]);
		}
	}

	return vecVerts;
}
