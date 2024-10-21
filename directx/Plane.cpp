#include "Plane.h"
#include "Vertex.h"

Plane::Plane(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, PLANE, blending), color(WHITE), height(1), width(1)
{
	this->color = WHITE;
	this->height = 1.0f;
	this->width = 1.0f;

	this->init();

	// Side Standing
	this->setScale(Vector3(0.65f, 1.0f, 1));
	this->rotateY(1.57f);
}

Plane::~Plane() {}

void Plane::initializeBuffers()
{
	// Set up the Index buffer.
	unsigned int indices[] = {
		//FRONT 0
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK 0
		4,5,6,
		6,7,4,
	};
	UINT size_indices = ARRAYSIZE(indices);
	this->ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indices, size_indices);
}

std::vector<Vertex3D> Plane::createVertices()
{
	std::vector<Vertex3D> vecVerts;

	// Set up the Vertex buffer.
	//Vertex3D vertices[] = { // Cube Vertices
	//	// FRONT FACE
	//	{ Vector3(-width, -height, 0),	this->color },
	//	{ Vector3(-width, height, 0),	this->color },
	//	{ Vector3(width, height, 0),	this->color },
	//	{ Vector3(width, -height, 0),	this->color },
	//	// BACK FACE
	//	{ Vector3(width, -height, 0),	this->color },
	//	{ Vector3(width, height, 0),	this->color },
	//	{ Vector3(-width, height, 0),	this->color },
	//	{ Vector3(-width, -height, 0),	this->color }
	//};

	Vertex3D vertices[] = { // Cube Vertices
		// FRONT FACE
		{ Vector3(-width, -height, 0),	PALEDOGWOOD },
		{ Vector3(-width, height, 0),	ROSYBROWN },
		{ Vector3(width, height, 0),	PUCE },
		{ Vector3(width, -height, 0),	ROSETAUPE },
		// BACK FACE
		{ Vector3(width, -height, 0),	this->color },
		{ Vector3(width, height, 0),	PINK },
		{ Vector3(-width, height, 0),	this->color },
		{ Vector3(-width, -height, 0),	PINK }
	};
	UINT size_list = ARRAYSIZE(vertices);

	for (int i = 0; i < size_list; i++) {
		vecVerts.push_back(vertices[i]);
	}

	return vecVerts;
}
