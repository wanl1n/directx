#include "MeshObject.h"

#include "GraphicsEngine.h"

MeshObject::MeshObject(std::string name, OBJECT_TYPE type) :
	GameObject(name, type) {

	texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
	mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	name = "Teapot";
	this->init();

	this->vb = mesh->getVertexBuffer();
	this->ib = mesh->getIndexBuffer();
}

MeshObject::~MeshObject() {}

void MeshObject::init()
{
	this->createVertexShader();
	this->createPixelShader();
	this->createConstantBuffer();

	this->calculateBounds();
}

void MeshObject::createVertexShader()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	//ShaderNames shaderNames;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	//ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);
	renderSystem->compileVertexShader(L"TexturedVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = renderSystem->createVertexShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();
}

void MeshObject::createPixelShader()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	renderSystem->compilePixelShader(L"TexturedPixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();
}

void MeshObject::createConstantBuffer()
{
	this->cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(Constant));
}

void MeshObject::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);
}

void MeshObject::draw()
{
	//ShaderNames shaderNames;
	//ShaderLibrary* shaderLib = ShaderLibrary::getInstance();
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	/*device->setRenderConfig(shaderLib->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME),
		shaderLib->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));*/

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	//// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);
	device->setTexture(texture);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->setIndexBuffer(this->ib);
	device->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

