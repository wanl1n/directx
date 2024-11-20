#include "SkyboxMeshObject.h"
#include "CameraManager.h"

SkyboxMeshObject::SkyboxMeshObject() : MeshObject(MESH_SKY) 
{
	this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\sky.jpg");
	this->setScale(Math::Vector3(FAR_PLANE));
	this->setPosition(Math::Vector3(0));

	//std::cout << "Skybox Mesh Object constructor." << std::endl;
}

SkyboxMeshObject::~SkyboxMeshObject() {}

void SkyboxMeshObject::createPixelShader()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	ShaderNames shaderNames;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	ShaderLibrary::getInstance()->requestPixelShaderData(shaderNames.SKYBOX_SHADER_NAME, &shaderByteCode, &sizeShader);
	//renderSystem->compilePixelShader(L"SkyboxShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();
}

void SkyboxMeshObject::update(float deltaTime, RECT viewport)
{
	this->setPosition(CameraManager::getInstance()->getActiveCamera()->getPosition());
	GameObject::update(deltaTime, viewport);
}

void SkyboxMeshObject::draw()
{
	//std::cout << "Mesh Object" << name << " draw()." << std::endl;
	GraphicsEngine::get()->getRenderSystem()->setRasterizerState(true);

	ShaderNames shaderNames;
	ShaderLibrary* shaderLib = ShaderLibrary::getInstance();
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	device->setRenderConfig(shaderLib->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME),
							shaderLib->getPixelShader(shaderNames.SKYBOX_SHADER_NAME));

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	//// Set Shaders.
	/*device->setVertexShader(vs);
	device->setPixelShader(ps);*/
	device->setTexture(texture);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->setIndexBuffer(this->ib);
	device->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}