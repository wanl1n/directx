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
	InputSystem::getInstance()->addListener(SceneWindow::getInstance());
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

	this->grid = new Grid("Grid", false);

	// Default Primitives
	GameObjectManager::getInstance()->addGameObject(PLANE);
	GameObjectManager::getInstance()->addGameObject(CUBE);
	GameObjectManager::getInstance()->addGameObject(CAPSULE);
	GameObjectManager::getInstance()->addGameObject(CYLINDER);
	GameObjectManager::getInstance()->addGameObject(SPHERE);
}

void SceneWindow::onCreate()
{
	Window::onCreate();
	srand(time(NULL));

	InputSystem::initialize();
}

void SceneWindow::onUpdate()
{
	Window::onUpdate();
	DeviceContext* device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, GRAY);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 3. Update all objects.
	InputSystem::getInstance()->update();
	this->grid->update(deltaTime, rc);
	GameObjectManager::getInstance()->update(deltaTime, rc);
	CameraManager::getInstance()->update(rc);

	// 4. Draw calls
	this->grid->draw();
	GameObjectManager::getInstance()->render();

	this->swapChain->present(true);

	// 5. Update Delta time.
	deltaTime = (float)EngineTime::getDeltaTime();

	// 6. Check for exit
	if (InputSystem::getInstance()->isKeyDown(27))
		exit(0);
}

void SceneWindow::onDestroy()
{
	Window::onDestroy();

	delete swapChain;
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

void SceneWindow::onMouseMove(const Point& mousePos) {} 
void SceneWindow::onLeftMouseDown(const Point& mousePos) {}
void SceneWindow::onRightMouseDown(const Point& mousePos) {}
void SceneWindow::onLeftMouseUp(const Point& mousePos) {}
void SceneWindow::onRightMouseUp(const Point& mousePos) {}