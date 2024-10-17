#include "GraphicsEngine.h"
#include "RenderSystem.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;
GraphicsEngine* GraphicsEngine::get() {
	/*if (sharedInstance == nullptr)
		sharedInstance = new GraphicsEngine();*/

	return sharedInstance;
}

GraphicsEngine::GraphicsEngine() {}

GraphicsEngine::~GraphicsEngine() {}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	delete sharedInstance;
	if (sharedInstance != NULL)
		sharedInstance->release();
}

bool GraphicsEngine::init()
{
	this->renderSystem = new RenderSystem();
	this->renderSystem->init();
	return true;
}

bool GraphicsEngine::release()
{
	delete renderSystem;
	return true;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return this->renderSystem;
}