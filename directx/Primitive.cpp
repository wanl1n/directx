#include "Primitive.h"

Primitive::Primitive(std::string name, OBJECT_TYPE type, bool blending) : 
	GameObject(name, type), alphaOn(blending) {}

Primitive::~Primitive() 
{
	delete vb;
	delete cb;
	delete ib;
	delete vs;
	delete ps;
	delete bs;
}

void Primitive::init()
{
	this->initializeBuffers();
	this->createVertexShader();
	this->createPixelShader();
	this->createConstantBuffer();
	this->createBlendState(alphaOn);
}

void Primitive::createVertexShader()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	std::vector<Vertex3D> vertices = this->createVertices();

	renderSystem->compileVertexShader(L"SolidVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = renderSystem->createVertexShader(shaderByteCode, sizeShader);
	this->vb = renderSystem->createVertexBuffer(vertices, sizeof(Vertex3D), shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();
}

void Primitive::createPixelShader()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	renderSystem->compilePixelShader(L"SolidPixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();
}

void Primitive::createConstantBuffer()
{
	this->cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(Constant));
}

void Primitive::createBlendState(bool blending)
{
	this->bs = GraphicsEngine::get()->getRenderSystem()->createBlendState(blending);
}

void Primitive::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &this->cc);
}

void Primitive::draw()
{
	DeviceContext* device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->setIndexBuffer(this->ib);
	device->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

