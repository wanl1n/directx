#include "GraphicsEngine.h"
#include "RenderSystem.h"
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
		throw std::exception("Graphics Engine not created successfully.");
	}
}

GraphicsEngine::~GraphicsEngine() 
{
	GraphicsEngine::sharedInstance = nullptr;
	delete renderSystem;
}

void GraphicsEngine::initialize()
{
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