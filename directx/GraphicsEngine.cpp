#include "GraphicsEngine.h"
#include <exception>

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;
GraphicsEngine* GraphicsEngine::get() {
	/*if (sharedInstance == nullptr)
		sharedInstance = new GraphicsEngine();*/

	return sharedInstance;
}

GraphicsEngine::GraphicsEngine() 
{
	try {
		this->renderSystem = new RenderSystem();
	}
	catch (...) { throw std::exception("Render System not created successfully."); }

	try {
		this->texManager = new TextureManager();
	}
	catch (...) { throw std::exception("Texture Manager not created successfully."); }

	try {
		this->meshManager = new MeshManager();
	}
	catch (...) { throw std::exception("Mesh Manager not created successfully."); }

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	this->renderSystem->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	::memcpy(meshLayoutByteCode, shaderByteCode, sizeShader);
	meshLayoutSize = sizeShader;
	this->renderSystem->releaseCompiledShader();
}

GraphicsEngine::~GraphicsEngine() 
{
	GraphicsEngine::sharedInstance = nullptr;
	delete meshManager;
	delete texManager;
	delete renderSystem;
}

void GraphicsEngine::initialize()
{
	//if (GraphicsEngine::sharedInstance) throw std::exception("Graphics Engine already created.");
	sharedInstance = new GraphicsEngine();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance == NULL)
		return;
	delete sharedInstance;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return this->renderSystem;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return this->texManager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return this->meshManager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byteCode, size_t* size)
{
	*byteCode = meshLayoutByteCode;
	*size = meshLayoutSize;
}
