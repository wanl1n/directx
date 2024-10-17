#include "Primitive.h"

Primitive::Primitive(std::string name, bool blending) : GameObject(name)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// 1. Creating Vertex Shader
	graphicsEngine->compileVertexShader(L"3DVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();

	// 2. Creating Pixel Shader
	graphicsEngine->compilePixelShader(L"3DPixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();

	// 3. Create a constant buffer.
	cc.time = 0;
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));

	// 4. Create a blend state.
	this->bs = GraphicsEngine::get()->createBlendState(blending);
}

Primitive::~Primitive()
{}

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

void Primitive::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cc);
}

void Primitive::draw()
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
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

