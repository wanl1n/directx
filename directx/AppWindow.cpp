#include "AppWindow.h"
#include "Windows.h"
#include "InputSystem.h"
#include "EngineTime.h"

#include "Constants.h"
#include "Vertex.h"

AppWindow* AppWindow::sharedInstance = nullptr;
AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init(1024, 1024);
}

AppWindow::AppWindow() {}
AppWindow::~AppWindow() {}

void AppWindow::initializeEngine()
{
	// Engine Time
	EngineTime::initialize();

	// Input System
	InputSystem::getInstance()->addListener(AppWindow::getInstance());
	//InputSystem::getInstance()->toggleCursor(false);

	// Game Object Manager
	GameObjectManager::initialize();
	CameraManager::initialize(this->getClientWindowRect());

	// Graphics Engine
	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Swap Chain
	RECT windowRect = this->getClientWindowRect();
	this->swapChain = graphicsEngine->getRenderSystem()->createSwapChain(this->hwnd, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	// Random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	GameObjectManager::getInstance()->addGameObject(CUBE);
	GameObjectManager::getInstance()->addGameObject(PLANE);
}

void AppWindow::onCreate() 
{
	Window::onCreate();
	srand(time(NULL));

	InputSystem::initialize();
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
	GameObjectManager::getInstance()->update(deltaTime, rc);
	CameraManager::getInstance()->update(rc);

	GameObjectManager::getInstance()->render();

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
	GraphicsEngine::get()->release();
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

void AppWindow::onMouseMove(const Point& mousePos)
{
}

void AppWindow::onLeftMouseDown(const Point& mousePos)
{
}

void AppWindow::onRightMouseDown(const Point& mousePos)
{
}

void AppWindow::onLeftMouseUp(const Point& mousePos)
{
}

void AppWindow::onRightMouseUp(const Point& mousePos)
{
}
