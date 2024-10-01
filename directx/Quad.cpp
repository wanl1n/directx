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
	cc.m_time = 0;

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

	Constant cc;
	m_time += 1.57f * deltaTime;
	cc.m_time = m_time;
	//cc.m_time = ::GetTickCount64();

	this->deltaPos += deltaTime / 1.0f;
	if (this->deltaPos > 1.0f) this->deltaPos = 0;

	Matrix4x4 temp;

	this->deltaScale += deltaTime / 0.15f;

	cc.m_world.setScale(Vector3::lerp(Vector3(0.5f, 0.5f, 0), Vector3(1, 1, 0), (sin(this->deltaScale) + 1.0f) / 2.0f));
	temp.setTranslation(Vector3::lerp(Vector3(-1.5f, -1.5f, 0), Vector3(1.5f, 1.5f, 0), this->deltaPos));
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(
		(viewport.right - viewport.left) / 400.0f,
		(viewport.bottom - viewport.top) / 400.0f,
		-4.0f, 4.0f
	);

	this->cb->update(device, &cc);

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);
}

void Quad::draw(VertexShader* vs, PixelShader* ps)
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);

	// Draw Object.
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->vb->getSizeVertexList(), 0);
}

