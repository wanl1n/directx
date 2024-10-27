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
}

SceneWindow::SceneWindow() : Window(720, 720) {}
SceneWindow::~SceneWindow() {}

void SceneWindow::initializeEngine()
{
	// Engine Time
	EngineTime::initialize();

	// Input System
	InputSystem::getInstance()->addListener(SceneWindow::getInstance());
	InputSystem::getInstance()->toggleCursor(false);

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
	GameObjectManager::getInstance()->addGameObject(LERPING_CUBE);
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
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, GRAY);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 3. Update all objects.
	InputSystem::getInstance()->update();
	this->grid->update(deltaTime, rc);
	GameObjectManager::getInstance()->update(deltaTime, rc);
	CameraManager::getInstance()->update();

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

	GraphicsEngine::get()->destroy();
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

void SceneWindow::testCase6()
{
	GameObjectManager::getInstance()->addGameObject(PLANE);
	GameObjectManager::getInstance()->addGameObject(CUBE, 3);

	// Cube 1
	GameObject* cube = GameObjectManager::getInstance()->findGameObject("Cube 1");
	cube->setPosition(Vector3(0, 0.9f, 0));

	cube = GameObjectManager::getInstance()->findGameObject("Cube 2");
	cube->setPosition(Vector3(-1.5f, 2.0f, 0));
	cube = GameObjectManager::getInstance()->findGameObject("Cube 3");
	cube->setPosition(Vector3(-1.5f, 3.0f, -2.0f));
}

void SceneWindow::testCase7()
{
	GameObjectManager::getInstance()->addGameObject(PLANE, 15);
	GameObject* plane;

	float distanceTris = 0.3f;
	float cardHeight = 1.9f;
	float cardAngle = 0.3f;
	float flip = 3.14f;
	
	// Base Tris
	plane = GameObjectManager::getInstance()->findGameObject("Plane 1");
	plane->rotateZ(-cardAngle + flip);
	plane->setPosition(Vector3(-distanceTris * 5, 0.0f, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 2");
	plane->rotateZ(cardAngle);
	plane->setPosition(Vector3(-distanceTris * 3, 0.0f, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 3");
	plane->rotateZ(-cardAngle + flip);
	plane->setPosition(Vector3(-distanceTris, 0.0f, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 4");
	plane->rotateZ(cardAngle);
	plane->setPosition(Vector3(distanceTris, 0.0f, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 5");
	plane->rotateZ(-cardAngle + flip);
	plane->setPosition(Vector3(distanceTris * 3, 0.0f, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 6");
	plane->rotateZ(cardAngle);
	plane->setPosition(Vector3(distanceTris * 5, 0.0f, 0.0f));

	// Base Ceils
	plane = GameObjectManager::getInstance()->findGameObject("Plane 7");
	plane->rotateZ(1.57f);
	plane->setPosition(Vector3(-distanceTris * 2, cardHeight * 0.5f, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 8");
	plane->rotateZ(1.57f);
	plane->setPosition(Vector3(distanceTris * 2, cardHeight * 0.5f, 0.0f));

	// Mid Tris
	plane = GameObjectManager::getInstance()->findGameObject("Plane 9");
	plane->rotateZ(-cardAngle + flip);
	plane->setPosition(Vector3(-distanceTris * 3, cardHeight * 1, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 10");
	plane->rotateZ(cardAngle);
	plane->setPosition(Vector3(-distanceTris, cardHeight * 1, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 11");
	plane->rotateZ(-cardAngle + flip);
	plane->setPosition(Vector3(distanceTris, cardHeight * 1, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 12");
	plane->rotateZ(cardAngle);
	plane->setPosition(Vector3(distanceTris * 3, cardHeight * 1, 0.0f));

	// Mid Ceils
	plane = GameObjectManager::getInstance()->findGameObject("Plane 13");
	plane->rotateZ(1.57f);
	plane->setPosition(Vector3(0.0f, cardHeight * 1.5f, 0.0f));

	// Top Tris
	plane = GameObjectManager::getInstance()->findGameObject("Plane 14");
	plane->rotateZ(-cardAngle + flip);
	plane->setPosition(Vector3(-distanceTris, cardHeight * 2, 0.0f));
	plane = GameObjectManager::getInstance()->findGameObject("Plane 15");
	plane->rotateZ(cardAngle);
	plane->setPosition(Vector3(distanceTris, cardHeight * 2, 0.0f));

}
