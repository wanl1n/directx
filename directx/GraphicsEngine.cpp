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
	catch (...) {
		throw std::exception("Render System not created successfully.");
	}

	try {
		this->texManager = new TextureManager();
	}
	catch (...) {
		throw std::exception("Texture Manager not created successfully.");
	}
}

GraphicsEngine::~GraphicsEngine() 
{
	GraphicsEngine::sharedInstance = nullptr;
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
