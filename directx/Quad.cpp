#include "Quad.h"
#include "Constant.h"

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader, QuadProps props, bool blending) : GameObject(name)
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

	// Transform				 RIGHT					  LEFT
	transform.position = Vector3((props.points1.point1.x + props.points1.point4.x) / 2,
								 (props.points1.point1.y + props.points1.point4.y) / 2,
								 props.points1.point1.z);
	//transform.position = props.points1.point2;
	std::cout << transform.position.x << ", " << transform.position.y << ", " << transform.position.z << std::endl;
	//transform.position = Vector3(0, 0, 0);
	cc.m_world.setTranslation(transform.position);

	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));

	this->bs = GraphicsEngine::get()->createBlendState(blending);

	this->height = props.points1.point2.y - props.points1.point1.y;
	this->width = props.points1.point3.x - props.points1.point1.x;
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
	GameObject::update(deltaTime);

	this->project(ORTHOGRAPHIC, viewport);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cc);
}

void Quad::draw(VertexShader* vs, PixelShader* ps)
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);

	// Draw Object.
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->vb->getSizeVertexList(), 0);
}

