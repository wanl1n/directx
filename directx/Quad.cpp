#include "Quad.h"
#include "Constant.h"

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, QuadProps props) : GameObject(name)
{
	Vertex vertices[] = {
		{ props.points1.point1,	props.points2.point1,	props.color1.color1,	props.color2.color1 },
		{ props.points1.point2,	props.points2.point2,	props.color1.color2,	props.color2.color2 },
		{ props.points1.point3,	props.points2.point3,	props.color1.color3,	props.color2.color3 },
		{ props.points1.point4,	props.points2.point4,	props.color1.color4,	props.color2.color4 }
	};

	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	Constant cc;
	cc.m_angle = 0;

	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));
}

Quad::~Quad()
{}

bool Quad::release()
{
	this->vb->release();
	this->cb->release();
	delete this;
	return true;
}

void Quad::update(float deltaTime, RECT viewport, VertexShader* vs, PixelShader* ps)
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();
	
	if (speedUp)
		m_angle += speed * 10 * deltaTime;
	else
		m_angle += speed * deltaTime;

	Constant cc;
	cc.m_angle = m_angle;

	this->cb->update(device, &cc);

	// Anim interval
	animIntervalCounter += deltaTime;

	if (animIntervalCounter >= 5) {
		speedUp = !speedUp;
		animIntervalCounter = 0;
	}

	std::cout << "animIntervalCounter: " << animIntervalCounter << std::endl;
	std::cout << "cc.m_angle: " << cc.m_angle << std::endl;

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);
}

void Quad::draw(VertexShader* vs, PixelShader* ps)
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->vb->getSizeVertexList(), 0);
}

