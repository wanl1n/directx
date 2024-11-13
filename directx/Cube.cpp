#include "Cube.h"

Cube::Cube(std::string name, bool blending, OBJECT_TYPE type) :
	Primitive(name, type, blending), side(1), frontColor(WHITE), backColor(WHITE)
{
	// Default Values
	this->side = 0.5f;
	this->size = Vector3(side * 2);
	this->frontColor = WHITE;
	this->backColor = WHITE;

	this->init();

	this->cc.world.setScale(Vector3(1));
	this->setPosition(Vector3(0, 0, 0));

	/*std::cout << "Bounds X: " << bounds.minX << ", " << bounds.maxX << std::endl;
	std::cout << "Bounds Y: " << bounds.minY << ", " << bounds.maxY << std::endl;
	std::cout << "Bounds Z: " << bounds.minZ << ", " << bounds.maxZ << std::endl;*/

	this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
}

Cube::~Cube() {}

void Cube::initializeBuffers()
{
	// Set up the Index buffer.
	//unsigned int indices[] = {
	//	//FRONT SIDE
	//	0,1,2,  //FIRST TRIANGLE
	//	2,3,0,  //SECOND TRIANGLE
	//	//BACK SIDE
	//	4,5,6,
	//	6,7,4,
	//	//TOP SIDE
	//	1,6,5,
	//	5,2,1,
	//	//BOTTOM SIDE
	//	7,0,3,
	//	3,4,7,
	//	//RIGHT SIDE
	//	3,2,5,
	//	5,4,3,
	//	//LEFT SIDE
	//	7,6,1,
	//	1,0,7
	//};

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

	//Vector3 xyzs[] = {
	//	// FRONT FACE
	//	Vector3(-side, -side, -side),
	//	Vector3(-side, side, -side),
	//	Vector3(side, side, -side),
	//	Vector3(side, -side, -side),
	//	// BACK FACE
	//	Vector3(side, -side, side),
	//	Vector3(side, side, side),	
	//	Vector3(-side, side, side),	
	//	Vector3(-side, -side, side)
	//};

	//Vector2 uvs[] = {
	//	Vector2(0, 0),
	//	Vector2(0, 1),
	//	Vector2(1, 0),
	//	Vector2(1, 1)
	//};

	Vector3 xyzs[] =
	{
		{ Vector3(-0.5f,-0.5f,-0.5f)},
		{ Vector3(-0.5f,0.5f,-0.5f) },
		{ Vector3(0.5f,0.5f,-0.5f) },
		{ Vector3(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3(0.5f,-0.5f,0.5f) },
		{ Vector3(0.5f,0.5f,0.5f) },
		{ Vector3(-0.5f,0.5f,0.5f)},
		{ Vector3(-0.5f,-0.5f,0.5f) }
	};

	Vector2 uvs[] =
	{
		{ Vector2(0.0f,0.0f) },
		{ Vector2(0.0f,1.0f) },
		{ Vector2(1.0f,0.0f) },
		{ Vector2(1.0f,1.0f) }
	};

	/*Vector4 rgbas_rb[] = { RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, PINK };
	Vector4 rgbas_wh[] = { frontColor, frontColor, frontColor, frontColor, 
						   backColor, backColor, backColor, backColor };*/

	// 1. Set up the Vertex buffer.
	Vertex3D vertices[] = { // Cube Vertices
		// FRONT FACE
		{ xyzs[0], uvs[1] },
		{ xyzs[1], uvs[0] },
		{ xyzs[2], uvs[2] },
		{ xyzs[3], uvs[3] },
		// BACK FACE
		{ xyzs[4], uvs[1] },
		{ xyzs[5], uvs[0] },
		{ xyzs[6], uvs[2] },
		{ xyzs[7], uvs[3] },

		{ xyzs[1], uvs[1] },
		{ xyzs[6], uvs[0] },
		{ xyzs[5], uvs[2] },
		{ xyzs[2], uvs[3] },

		{ xyzs[7], uvs[1] },
		{ xyzs[0], uvs[0] },
		{ xyzs[3], uvs[2] },
		{ xyzs[4], uvs[3] },

		{ xyzs[3], uvs[1] },
		{ xyzs[2], uvs[0] },
		{ xyzs[5], uvs[2] },
		{ xyzs[4], uvs[3] },

		{ xyzs[7], uvs[1] },
		{ xyzs[6], uvs[0] },
		{ xyzs[1], uvs[2] },
		{ xyzs[0], uvs[3] }
	};
	UINT size_list = ARRAYSIZE(vertices);

	for (int i = 0; i < size_list; i++) {
		vecVerts.push_back(vertices[i]);
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
