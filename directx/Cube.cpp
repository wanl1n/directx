#include "Cube.h"

Cube::Cube(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, type, blending), side(1), frontColor(WHITE), backColor(WHITE)
{
	this->init();

	// Lying down
	this->transform.position = Vector3(5, 1.1f, 5);
	this->cc.world.setIdentity();
	this->cc.world.setTranslation(this->transform.position);
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

	// Default Values
	this->side = 1.0f;
	this->frontColor = WHITE;
	this->backColor = PINK;

	// 1. Set up the Vertex buffer.
	Vertex3D vertices[] = { // Cube Vertices
		// FRONT FACE
		{ Vector3(-side, -side, -side), REDCARPET },
		{ Vector3(-side, side, -side),	REDRAMPAGE },
		{ Vector3(side, side, -side),	CORALROSE },
		{ Vector3(side, -side, -side),	SCOTCHMIST },
		// BACK FACE
		{ Vector3(side, -side, side),	REDCARPET },
		{ Vector3(side, side, side),	REDRAMPAGE },
		{ Vector3(-side, side, side),	CORALROSE },
		{ Vector3(-side, -side, side),	SCOTCHMIST }
	};
	UINT size_list = ARRAYSIZE(vertices);

	for (int i = 0; i < size_list; i++) {
		vecVerts.push_back(vertices[i]);
	}

	return vecVerts;
}
