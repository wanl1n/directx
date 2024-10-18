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

	// Graphics Engine
	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Swap Chain
	RECT windowRect = this->getClientWindowRect();
	this->swapChain = graphicsEngine->getRenderSystem()->createSwapChain(this->hwnd, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	// Random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	this->grid = new Grid("Grid", false);

	this->worldCamera.setIdentity();
	this->worldCamera.setTranslation(Vector3(0, 0, -6));

	// Default Primitives
	//GameObjectManager::getInstance()->addGameObject(PLANE);
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

	// Input System Update:
	InputSystem::getInstance()->update();
	// Scene Tools Update:
	this->grid->update(deltaTime, rc);
	// Game Object Manager Update:
	GameObjectManager::getInstance()->update(deltaTime, rc);

	// Camera
	Matrix4x4 worldCam;
	Matrix4x4 temp;

	worldCam.setIdentity();
	temp.setIdentity();
	temp.setRotationX(this->rotX);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->rotY);
	worldCam *= temp;

	Vector3 newPos = worldCamera.getTranslation() + worldCam.getZDir() * (this->forward * 0.3f);
	newPos += worldCam.getXDir() * (this->rightward * 0.3f);

	worldCam.setTranslation(newPos);
	worldCamera = worldCam;
	worldCam.inverse();

	GameObjectManager::getInstance()->updateCameraView(worldCam);
	GameObjectManager::getInstance()->setProjection(PERSPECTIVE, rc);

	// Draw calls
	this->grid->draw();
	GameObjectManager::getInstance()->render();

	this->swapChain->present(true);

	// Update Delta time.
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
	//std::cout << "Key down." << std::endl;
	switch (key) {
		case 'W':
			this->forward = 1.0f;
			break;
		case 'A':
			this->rightward = -1.0f;
			break;
		case 'S':
			this->forward = -1.0f;
			break;
		case 'D':
			this->rightward = 1.0f;
			break;
		case 27: // Escape
			exit(0);
			break;
	}
	//std::cout << key << std::endl;
}

void SceneWindow::onKeyUp(int key)
{
	this->forward = 0;
	this->rightward = 0;

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

	float speed = 0.1f;
	this->rotX += (mousePos.y - (height/2.0f)) * deltaTime * speed;
	this->rotY += (mousePos.x - (width/2.0f)) * deltaTime * speed;

	InputSystem::getInstance()->setCursorPosition(Point(width/2.0f, height/2.0f));
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