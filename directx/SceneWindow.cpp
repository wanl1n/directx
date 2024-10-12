#include "SceneWindow.h"
#include "Windows.h"
#include "InputSystem.h"
#include "EngineTime.h"

#include "Constants.h"
#include "Vertex.h"

SceneWindow* SceneWindow::sharedInstance = nullptr;
SceneWindow* SceneWindow::getInstance()
{
	return sharedInstance;
}

void SceneWindow::initialize()
{
	sharedInstance = new SceneWindow();
	sharedInstance->init(1080, 1080);
}

SceneWindow::SceneWindow() {}
SceneWindow::~SceneWindow() {}

void SceneWindow::initializeEngine()
{
	// Engine Time
	EngineTime::initialize();

	// Input System
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(SceneWindow::getInstance());

	// Game Object Manager
	GameObjectManager::initialize();

	// Graphics Engine
	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Swap Chain
	this->swapChain = graphicsEngine->createSwapChain();
	RECT windowRect = this->getClientWindowRect();
	this->swapChain->init(this->hwnd, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	// Random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	this->grid = new Grid("Grid", true);

	GameObjectManager::getInstance()->addGameObject(CUBE);
	GameObjectManager::getInstance()->addGameObject(ROTATING_PLANE);
}

void SceneWindow::onCreate()
{
	Window::onCreate();
}

void SceneWindow::onUpdate()
{
	Window::onUpdate();

	// Input System Update.
	InputSystem::getInstance()->update();

	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, PINK);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::getInstance()->update(deltaTime, rc);
	GameObjectManager::getInstance()->render();

	this->swapChain->present(true);

	// Update Delta time.
	deltaTime = (float)EngineTime::getDeltaTime();
}

void SceneWindow::onDestroy()
{
	Window::onDestroy();

	this->swapChain->release();
	GraphicsEngine::get()->release();
}

void SceneWindow::onFocus()
{
	if (!InputSystem::getInstance()) InputSystem::initialize();
	InputSystem::getInstance()->addListener(SceneWindow::getInstance());
}

void SceneWindow::onKillFocus()
{
	if (!InputSystem::getInstance()) InputSystem::initialize();
	InputSystem::getInstance()->removeListener(SceneWindow::getInstance());
}

void SceneWindow::onKeyDown(int key)
{
	//std::cout << "Key down." << std::endl;
	switch (key) {
		case 27: // Escape
			exit(0);
			break;
	}
	//std::cout << key << std::endl;
}

void SceneWindow::onKeyUp(int key)
{
	switch (key) {
		case ' ': // Spacebar
			break;
		case 8: // Backspace
			break;
		case 46: // Delete
			break;
	}
}

void SceneWindow::onMouseMove(const Point& deltaMousePos)
{
}

void SceneWindow::onLeftMouseDown(const Point& mousePos)
{
}

void SceneWindow::onRightMouseDown(const Point& mousePos)
{
}

void SceneWindow::onLeftMouseUp(const Point& mousePos)
{
}

void SceneWindow::onRightMouseUp(const Point& mousePos)
{
}