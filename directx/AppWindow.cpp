#include "AppWindow.h"
#include "Windows.h"
#include "InputSystem.h"
#include "EngineTime.h"

#include "Constants.h"
#include "Vertex.h"
#include <cstdlib>
#include <ctime>

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
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(AppWindow::getInstance());

	// Game Object Manager
	GameObjectManager::initialize();

	// Graphics Engine
	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Swap Chain
	this->swapChain = graphicsEngine->getRenderSystem()->createSwapChain();
	RECT windowRect = this->getClientWindowRect();
	this->swapChain->init(this->hwnd, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	// Random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	GameObjectManager::getInstance()->addGameObject(ROTATING_CUBE, 100);
}

void AppWindow::onCreate() 
{
	Window::onCreate();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	// Input System Update.
	InputSystem::getInstance()->update();

	DeviceContext* device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, MATCHA);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	this->rotX += deltaTime;
	this->rotY += deltaTime;

	GameObjectManager::getInstance()->update(deltaTime, rc);
	GameObjectManager::getInstance()->render();

	this->swapChain->present(true);

	// Update Delta time.
	deltaTime = (float)EngineTime::getDeltaTime();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	this->swapChain->release();
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

void AppWindow::onKeyDown(int key)
{
	//std::cout << "Key down." << std::endl;
	switch (key) {
		case 'W':
			//this->rotX += 0.707f * deltaTime;
			break;
		case 'S':
			//this->rotX -= 0.707f * deltaTime;
			break;
		case 'A':
			//this->rotY += 0.707f * deltaTime;
			break;
		case 'D':
			//this->rotY -= 0.707f * deltaTime;
			break;
		case 27: // Escape
			exit(0);
			break;

	}
	//std::cout << key << std::endl;
}

void AppWindow::onKeyUp(int key)
{
	//switch (key) {
	//	case ' ': // Spacebar
	//		this->createCube();
	//		break;
	//	case 8: // Backspace
	//		if (this->CircleList.size() > 0)
	//			this->CircleList.pop_back();
	//		break;
	//	case 46: // Delete
	//		if (this->CircleList.size() > 0)
	//			this->CircleList.clear();
	//		break;
	//}
}

void AppWindow::onMouseMove(const Point& mousePos)
{
	/*this->rotX -= deltaMousePos.y * deltaTime;
	this->rotY -= deltaMousePos.x * deltaTime;*/
}

void AppWindow::onLeftMouseDown(const Point& mousePos)
{
	//this->scaler = 0.5f;
}

void AppWindow::onRightMouseDown(const Point& mousePos)
{
	//this->scaler = 2.0f;
}

void AppWindow::onLeftMouseUp(const Point& mousePos)
{
	//this->scaler = 1.0f;
}

void AppWindow::onRightMouseUp(const Point& mousePos)
{
	//this->scaler = 1.0f;
}
