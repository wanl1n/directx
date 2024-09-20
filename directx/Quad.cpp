#include "Quad.h"

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, Vertex centerVert, 
			float width, float height) : GameObject(name)
{
	this->centerVert = centerVert;
	this->width = width;
	this->height = height;

	float left = centerVert.position.x - (width / 2);
	float right = centerVert.position.x + (width / 2);
	float top = centerVert.position.y + (height / 2);
	float bottom = centerVert.position.y - (height / 2);
	//this->bounds = { left, top, right, bottom };

	Vertex vertices[] = {
		{ left,		bottom, 0.0f,	centerVert.color },
		{ left,		top,	0.0f,	centerVert.color },
		{ right,	bottom, 0.0f,	centerVert.color },
		{ right,	top,	0.0f,	centerVert.color }
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	std::cout << "Created a solid quad." << std::endl;
}

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, Vertex centerVert, 
			float width, float height, Vector3D leftColor, Vector3D rightColor) : GameObject(name)
{
	this->centerVert = centerVert;
	this->width = width;
	this->height = height;

	float left = centerVert.position.x - (width / 2);
	float right = centerVert.position.x + (width / 2);
	float top = centerVert.position.y + (height / 2);
	float bottom = centerVert.position.y - (height / 2);
	//this->bounds = { left, top, right, bottom };

	Vertex vertices[] = {
		{ left,		bottom, 0.0f,	leftColor },
		{ left,		top,	0.0f,	leftColor },
		{ right,	bottom, 0.0f,	rightColor },
		{ right,	top,	0.0f,	rightColor }
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);
	
	std::cout << "Created a 2-color gradient quad." << std::endl;
}

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, Vertex centerVert, 
			float width, float height, Vector3D color1, Vector3D color2, Vector3D color3, Vector3D color4) : GameObject(name)
{
	this->centerVert = centerVert;
	this->width = width;
	this->height = height;

	float left = centerVert.position.x - (width / 2);
	float right = centerVert.position.x + (width / 2);
	float top = centerVert.position.y + (height / 2);
	float bottom = centerVert.position.y - (height / 2);
	//this->bounds = { left, top, right, bottom };

	Vertex vertices[] = {
		{ left,		bottom, 0.0f,	color1 },
		{ left,		top,	0.0f,	color2 },
		{ right,	bottom, 0.0f,	color3 },
		{ right,	top,	0.0f,	color4 }
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);
	
	std::cout << "Created a 4-color quad." << std::endl;
}

Quad::~Quad()
{
}

bool Quad::release()
{
	this->m_vb->release();
	delete this;
	return true;
}

void Quad::draw(VertexShader* vs, PixelShader* ps)
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
}

