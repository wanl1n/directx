#include "Quad.h"
#include "Constant.h"

Quad::Quad(std::string name, QuadProps props) : GameObject(name)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);

	Vertex vertices[] = {
		{ props.points1.point1,	props.points2.point1,	props.color1.color1,	props.color2.color1 },
		{ props.points1.point2,	props.points2.point2,	props.color1.color2,	props.color2.color2 },
		{ props.points1.point3,	props.points2.point3,	props.color1.color3,	props.color2.color3 },
		{ props.points1.point4,	props.points2.point4,	props.color1.color4,	props.color2.color4 }
	};

	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->vb->load(vertices, sizeof(Vertex), size_list, shaderByteCode, sizeShader);

	Constant cc;
	cc.m_angle = 0;

	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));

	graphicsEngine->releaseCompiledShader();

	// Creating Pixel Shader
	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();
}

Quad::~Quad()
{}

bool Quad::release()
{
	this->vb->release();
	this->cb->release();
	this->vs->release();
	this->ps->release();
	delete this;	
	return true;
}

void Quad::update(float deltaTime, RECT viewport)
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();
	
	if (speedUp) m_angle += speed * 10 * deltaTime;
	else m_angle += speed * deltaTime;

	Constant cc;
	cc.m_angle = m_angle;

	this->cb->update(device, &cc);

	// Anim interval
	animIntervalCounter += deltaTime;

	if (animIntervalCounter >= 5) {
		speedUp = !speedUp;
		animIntervalCounter = 0;
	}

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// 4. Set Shaders.
	device->setVertexShader(this->vs);
	device->setPixelShader(this->ps);
}

void Quad::draw()
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->vb->getSizeVertexList(), 0);
}

