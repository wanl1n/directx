#include "Primitive.h"
#include "InputSystem.h"

Primitive::Primitive(std::string name, OBJECT_TYPE type, bool blending) : 
	GameObject(name, type), alphaOn(blending) {}

Primitive::~Primitive() {}

void Primitive::init()
{
	this->initializeBuffers();
	this->createVertexShader();
	this->createPixelShader();
	this->createConstantBuffer();
	this->createBlendState(alphaOn);

	this->calculateBounds();
}

void Primitive::createVertexShader()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	ShaderNames shaderNames;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	std::vector<Vertex3D> vertices = this->createVertices();

	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);
	//renderSystem->compileVertexShader(L"TexturedVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
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

	renderSystem->compilePixelShader(L"TexturedPixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
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
}

void Primitive::draw()
{
	ShaderNames shaderNames;
	ShaderLibrary* shaderLib = ShaderLibrary::getInstance();
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	device->setRenderConfig(shaderLib->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME),
							shaderLib->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	//// Set Shaders.
	//device->setVertexShader(vs);
	//device->setPixelShader(ps);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->setIndexBuffer(this->ib);
	device->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

