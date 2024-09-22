#include "Quad.h"
#include "Constant.h"

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, Vertex centerVert, 
			float width, float height) : GameObject(name)
{
	this->centerVert = centerVert;
	this->width = width;
	this->height = height;
	this->calculateBounds(true);

	Vertex vertices[] = {
		{ bounds.left,		bounds.bottom,	0.0f,	target.left,	target.bottom,	0.0f,	centerVert.color,	centerVert.color1 },
		{ bounds.left,		bounds.top,		0.0f,	target.left,	target.top,		0.0f,	centerVert.color,	centerVert.color1 },
		{ bounds.right,		bounds.bottom,	0.0f,	target.right,	target.bottom,	0.0f,	centerVert.color,	centerVert.color1 },
		{ bounds.right,		bounds.top,		0.0f,	target.right,	target.top,		0.0f,	centerVert.color,	centerVert.color1 }
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);
}

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, Vertex centerVert, 
			float width, float height, DuoColor color) : GameObject(name)
{
	this->centerVert = centerVert;
	this->width = width;
	this->height = height;
	this->calculateBounds(true);

	Vertex vertices[] = {
		{ bounds.left,		bounds.bottom,	0.0f,	target.left,	target.bottom,	0.0f,	color.color1,	color.color2 },
		{ bounds.left,		bounds.top,		0.0f,	target.left,	target.top,		0.0f,	color.color1,	color.color2 },
		{ bounds.right,		bounds.bottom,	0.0f,	target.right,	target.bottom,	0.0f,	color.color2,	color.color1 },
		{ bounds.right,		bounds.top,		0.0f,	target.right,	target.top,		0.0f,	color.color2,	color.color1 }
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);
}

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, Vertex centerVert, 
			float width, float height, QuadColor color) : GameObject(name)
{
	this->centerVert = centerVert;
	this->width = width;
	this->height = height;
	this->calculateBounds(true);

	Vertex vertices[] = {
		{ bounds.left,		bounds.bottom,	0.0f,	target.left,	target.bottom,	0.0f,	color.color1,	color.color4 },
		{ bounds.left,		bounds.top,		0.0f,	target.left,	target.top,		0.0f,	color.color2,	color.color1 },
		{ bounds.right,		bounds.bottom,	0.0f,	target.right,	target.bottom,	0.0f,	color.color3,	color.color2 },
		{ bounds.right,		bounds.top,		0.0f,	target.right,	target.top,		0.0f,	color.color4,	color.color3 }
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);
}

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, Vertex centerVert, 
			float width, float height, QuadColor color, QuadVertex targetPoints) : GameObject(name)
{
	this->centerVert = centerVert;
	this->width = width;
	this->height = height;
	this->calculateBounds(false);

	Vertex vertices[] = {
		{ bounds.left,		bounds.bottom,	0.0f,	targetPoints.point1,	color.color1,	color.color4 },
		{ bounds.left,		bounds.top,		0.0f,	targetPoints.point2,	color.color2,	color.color1 },
		{ bounds.right,		bounds.bottom,	0.0f,	targetPoints.point3,	color.color3,	color.color2 },
		{ bounds.right,		bounds.top,		0.0f,	targetPoints.point4,	color.color4,	color.color3 }
	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);
}

Quad::~Quad()
{}

void Quad::calculateBounds(bool moving)
{
	float left = centerVert.position.x - (width / 2);
	float right = centerVert.position.x + (width / 2);
	float top = centerVert.position.y + (height / 2);
	float bottom = centerVert.position.y - (height / 2);

	this->bounds = { left, top, right, bottom };

	if (moving)
		this->calculateTarget();
	else
		this->target = this->bounds;
}

void Quad::calculateTarget()
{
	float left = centerVert.position1.x - (width / 2);
	float right = centerVert.position1.x + (width / 2);
	float top = centerVert.position1.y + (height / 2);
	float bottom = centerVert.position1.y - (height / 2);

	std::cout << left << " " << right << " " << top << " " << bottom << std::endl;

	this->target = { left, top, right, bottom };
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

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
}

