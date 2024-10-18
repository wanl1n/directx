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
	InputSystem::getInstance()->toggleCursor(false);

	// Game Object Manager
	GameObjectManager::initialize();
	CameraManager::initialize();

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
	GameObjectManager::getInstance()->addGameObject(CAPSULE);
	GameObjectManager::getInstance()->addGameObject(SPHERE);
}

void SceneWindow::onCreate()
{
	Window::onCreate();
}

void SceneWindow::onUpdate()
{
	Window::onUpdate();
	DeviceContext* device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, BLACK);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 3. Update all objects.
	InputSystem::getInstance()->update();
	this->grid->update(deltaTime, rc);
	GameObjectManager::getInstance()->update(deltaTime, rc);
	CameraManager::getInstance()->update(rc);

	GameObjectManager::getInstance()->updateCameraView(CameraManager::getInstance()->getActiveCameraView());
	GameObjectManager::getInstance()->setProjection(CameraManager::getInstance()->getActiveProjection());

	// 4. Draw calls
	this->grid->draw();
	GameObjectManager::getInstance()->render();

	this->swapChain->present(true);

	// 5. Update Delta time.
	deltaTime = (float)EngineTime::getDeltaTime();
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

void SceneWindow::onKeyDown(int key)
{
	switch (key) {
		/*case 'W':
			CameraManager::getInstance()->getActiveCamera()->setForward(1.0f);
			break;
		case 'A':
			CameraManager::getInstance()->getActiveCamera()->setRightward(-1.0f);
			break;
		case 'S':
			CameraManager::getInstance()->getActiveCamera()->setForward(-1.0f);
			break;
		case 'D':
			CameraManager::getInstance()->getActiveCamera()->setRightward(1.0f);
			break;*/
		case 27: // Escape
			exit(0);
			break;
	}
}

void SceneWindow::onKeyUp(int key)
{
	/*CameraManager::getInstance()->getActiveCamera()->setForward(0);
	CameraManager::getInstance()->getActiveCamera()->setRightward(0);*/

	switch (key) {
		case ' ': // Spacebar
			break;
		case 8: // Backspace
			break;
		case 46: // Delete
			break;
		case '1': // 1
			break;
		case '2': // 2
			break;
	}
}

void SceneWindow::onMouseMove(const Point& mousePos)
{
	RECT viewport = this->getClientWindowRect();
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);

	float speed = CameraManager::getInstance()->getActiveCamera()->getPanSpeed();
	float deltaRotX = (mousePos.y - (height/2.0f)) * deltaTime * speed;
	float deltaRotY = (mousePos.x - (width/2.0f)) * deltaTime * speed;

	InputSystem::getInstance()->setCursorPosition(Point(width/2.0f, height/2.0f));

	CameraManager::getInstance()->getActiveCamera()->setRotationX(deltaRotX);
	CameraManager::getInstance()->getActiveCamera()->setRotationY(deltaRotY);
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