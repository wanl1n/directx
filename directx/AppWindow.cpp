#include "AppWindow.h"
#include <exception>

#include "InputSystem.h"
#include "EngineTime.h"
#include "TextureManager.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

#include "Constants.h"
#include "Vertex.h"

#include "Mesh.h"

AppWindow* AppWindow::sharedInstance = nullptr;
AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
}

AppWindow::AppWindow() : Window() {}
AppWindow::~AppWindow() {}

void AppWindow::initializeEngine()
{
	// Engine Time
	EngineTime::initialize();

	// Input System
	try { InputSystem::initialize(); }
	catch (...) { throw std::exception("Input System Initialization failed."); }
	InputSystem::getInstance()->addListener(AppWindow::getInstance());
	//InputSystem::getInstance()->toggleCursor(false);

	// Graphics Engine
	try { GraphicsEngine::initialize(); }
	catch (...) { throw std::exception("Graphics Engine Initialization failed."); }
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	ShaderLibrary::initialize();
	BaseComponentSystem::initialize();

	// Game Object Manager
	GameObjectManager::initialize();
	CameraManager::initialize(this->getClientWindowRect());
	try { UIManager::initialize(hwnd); }
	catch (...) { throw std::exception("UIManager Initialization failed."); }

	// Swap Chain
	RECT windowRect = this->getClientWindowRect();
	this->swapChain = graphicsEngine->getRenderSystem()->createSwapChain(this->hwnd, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	// Random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	GameObjectManager::getInstance()->addGameObject(CUBE, 10);
	GameObjectManager::getInstance()->addGameObject(PLANE);
}

void AppWindow::onCreate() 
{
	Window::onCreate();
	srand((unsigned int)time(NULL));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, PINK);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Update.
	InputSystem::getInstance()->update();
	CameraManager::getInstance()->update();
	GameObjectManager::getInstance()->update(deltaTime, rc);

	if (this->isPlaying) 
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();

	GameObjectManager::getInstance()->render();
	UIManager::getInstance()->render();

	this->swapChain->present(true);

	// Update Delta time.
	deltaTime = (float)EngineTime::getDeltaTime();

	// 6. Check for exit
	if (InputSystem::getInstance()->isKeyDown(27))
		exit(0);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::get()->destroy();
	InputSystem::getInstance()->destroy();
	GameObjectManager::getInstance()->destroy();
	CameraManager::getInstance()->destroy();
}

void AppWindow::onFocus()
{
	if (!InputSystem::getInstance()) InputSystem::initialize();
	InputSystem::getInstance()->addListener(AppWindow::getInstance());
}

void AppWindow::onKillFocus()
{
	if (!InputSystem::getInstance()) InputSystem::initialize();
	InputSystem::getInstance()->removeListener(AppWindow::getInstance());
}

void AppWindow::onMouseMove(const Math::Vector2& mousePos)
{
}

void AppWindow::onLeftMouseDown(const Math::Vector2& mousePos)
{
}

void AppWindow::onRightMouseDown(const Math::Vector2& mousePos)
{
}

void AppWindow::onLeftMouseUp(const Math::Vector2& mousePos)
{
}

void AppWindow::onRightMouseUp(const Math::Vector2& mousePos)
{
}

bool AppWindow::getPlaying()
{
	return isPlaying;
}

void AppWindow::setPlaying(bool playing)
{
	isPlaying = playing;
}
