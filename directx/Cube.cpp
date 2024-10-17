#include "Cube.h"

Cube::Cube(std::string name, CubeVertex props, bool blending) : Primitive(name, blending)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	this->side = 0.3f;

	// 1. Set up the Vertex buffer.
	CubeVertex vertices[] = { // Cube Vertices
		// FRONT FACE
		{ Vector3(-side, -side, -side), props.color1, props.color1 },
		{ Vector3(-side, side, -side),	props.color1, props.color1 },
		{ Vector3(side, side, -side),	props.color1, props.color1 },
		{ Vector3(side, -side, -side),	props.color1, props.color1 },
		// BACK FACE
		{ Vector3(side, -side, side),	props.color2, props.color2 },
		{ Vector3(side, side, side),	props.color2, props.color2 },
		{ Vector3(-side, side, side),	props.color2, props.color2 },
		{ Vector3(-side, -side, side),	props.color2, props.color2 }
	};
	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);

	// 2. Set up the Index buffer.
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
	this->ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_indices = ARRAYSIZE(indices);

	// Load into buffers.
	this->ib->load(indices, size_indices);
	this->vb->loadIndexed(vertices, sizeof(CubeVertex), size_list, shaderByteCode, sizeShader);
}

Cube::~Cube()
{}
