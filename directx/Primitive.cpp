#include "Primitive.h"

Primitive::Primitive(std::string name, bool blending) : 
	GameObject(name), alphaOn(blending) {}

Primitive::~Primitive() {}

void Primitive::init()
{
	this->initializeBuffers();
	this->createVertexShader();
	this->createPixelShader();
	this->createConstantBuffer();
	this->createBlendState(alphaOn);
}

bool Primitive::release()
{
	this->vb->release();
	this->cb->release();
	this->ib->release();

	this->vs->release();
	this->ps->release();

	this->bs->release();

	delete this;
	return true;
}

void Primitive::createVertexShader()
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	std::vector<Vertex3D> vertices = this->createVertices();
	this->vb = GraphicsEngine::get()->createVertexBuffer();

	graphicsEngine->compileVertexShader(L"SolidVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);
	this->vb->loadIndexed(vertices, sizeof(Vertex3D), vertices.size(), shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();
}

void Primitive::createPixelShader()
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	graphicsEngine->compilePixelShader(L"SolidPixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();
}

void Primitive::createConstantBuffer()
{
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));
}

void Primitive::createBlendState(bool blending)
{
	this->bs = GraphicsEngine::get()->createBlendState(blending);
}

void Primitive::update(float deltaTime, RECT viewport)
{
	std::cout << "Updating " << name << "." << std::endl;
	GameObject::update(deltaTime, viewport);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cc);
}

void Primitive::draw()
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();
	std::cout << "Drawing " << name << ". " << device << std::endl;

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);

	// Draw Object.
	std::cout << "Loading Index Buffer " << ib << ". " << std::endl;
	std::cout << "Loading Vertex Buffer " << vb << ". " << std::endl;
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

