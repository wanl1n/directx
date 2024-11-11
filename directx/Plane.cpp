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
	this->setScale(Vector3(5));
	this->rotateX(1.57f);
	this->setPosition(Vector3(0, -1.5f, 0));
	this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Logo.jpg");
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

	Point uvs[] = {
		Point(0, 0),
		Point(0, 1),
		Point(1, 0),
		Point(1, 1)
	};

	//Set up the Vertex buffer.
	if (COLOR_SETTINGS == WHITE_COLORED) {
		Vertex3D vertices[] = { // Cube Vertices
			// FRONT FACE
			{ Vector3(-width, -height, 0),	this->color , uvs[1]},
			{ Vector3(-width, height, 0),	this->color , uvs[0]},
			{ Vector3(width, height, 0),	this->color , uvs[2]},
			{ Vector3(width, -height, 0),	this->color , uvs[3]},
			// BACK FACE
			{ Vector3(width, -height, 0),	this->color , uvs[1]},
			{ Vector3(width, height, 0),	this->color , uvs[0]},
			{ Vector3(-width, height, 0),	this->color , uvs[2]},
			{ Vector3(-width, -height, 0),	this->color , uvs[3]}
		};
		UINT size_list = ARRAYSIZE(vertices);

		for (int i = 0; i < size_list; i++) {
			vecVerts.push_back(vertices[i]);
		}
	}
	else if (COLOR_SETTINGS == RAINBOW_COLORED) {

		Vertex3D vertices[] = { // Cube Vertices
			// FRONT FACE
			{ Vector3(-width, -height, 0),	PALEDOGWOOD, uvs[1] },
			{ Vector3(-width, height, 0),	ROSYBROWN, uvs[0] },
			{ Vector3(width, height, 0),	PUCE, uvs[2] },
			{ Vector3(width, -height, 0),	ROSETAUPE, uvs[3] },
			// BACK FACE
			{ Vector3(width, -height, 0),	this->color, uvs[1] },
			{ Vector3(width, height, 0),	PINK, uvs[0] },
			{ Vector3(-width, height, 0),	this->color, uvs[2] },
			{ Vector3(-width, -height, 0),	PINK, uvs[3] }
		};
		UINT size_list = ARRAYSIZE(vertices);

		for (int i = 0; i < size_list; i++) {
			vecVerts.push_back(vertices[i]);
		}
	}

	return vecVerts;
}
