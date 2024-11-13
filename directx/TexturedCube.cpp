#include "TexturedCube.h"

TexturedCube::TexturedCube(std::string name, bool blending, OBJECT_TYPE type) : Cube(name, blending, type)
{
	this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
}

TexturedCube::~TexturedCube() {}

void TexturedCube::initializeBuffers()
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

std::vector<Vertex3D> TexturedCube::createVertices()
{
	std::vector<Vertex3D> vecVerts;

	Vector3 xyzs[] = {
		// FRONT FACE
		Vector3(-side, -side, -side),
		Vector3(-side, side, -side),
		Vector3(side, side, -side),
		Vector3(side, -side, -side),
		// BACK FACE
		Vector3(side, -side, side),
		Vector3(side, side, side),
		Vector3(-side, side, side),
		Vector3(-side, -side, side)
	};

	Vector2 uvs[] =
	{
		{ Vector2(0.0f,0.0f) },
		{ Vector2(0.0f,1.0f) },
		{ Vector2(1.0f,0.0f) },
		{ Vector2(1.0f,1.0f) }
	};

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

void TexturedCube::draw()
{
	ShaderNames shaderNames;
	ShaderLibrary* shaderLib = ShaderLibrary::getInstance();
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	device->setRenderConfig(shaderLib->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME),
							shaderLib->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	/*device->setVertexShader(vs);
	device->setPixelShader(ps);*/
	device->setTexture(texture);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->setIndexBuffer(this->ib);
	device->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}
