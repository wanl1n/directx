#include "AppWindow.h"
#include "Windows.h"
#include "InputSystem.h"
#include "EngineTime.h"

#include "Constants.h"
#include "Constant.h"
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
	sharedInstance->init(1024, 768);
}

AppWindow::AppWindow() {}
AppWindow::~AppWindow() {}

void AppWindow::onCreate() 
{
	Window::onCreate();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	// Input System Update.
	InputSystem::getInstance()->update();

	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, 0, 0, 0, 1);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//std::cout << "Current Game Object Count: " << this->GOList.size() << std::endl;

	// 3. Update Game Objects.
	for (Circle* obj : this->CircleList)
		obj->update(deltaTime, rc);

	// 4. Draw all Game Objects.
	for (Circle* obj : this->CircleList)
		obj->draw();

	this->swapChain->present(true);

	// Update Delta time.
	deltaTime = EngineTime::getDeltaTime();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	for (Circle* gameObject : CircleList) {
		if (gameObject) gameObject->release();
	}

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

void AppWindow::initializeEngine()
{
	EngineTime::initialize();
	// Input System
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(AppWindow::getInstance());

	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	this->swapChain = graphicsEngine->createSwapChain();

	RECT windowRect = this->getClientWindowRect();
	this->swapChain->init(this->hwnd, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
}

void AppWindow::createCircle()
{
	CircleProps prop = {
		Vector3(0, 0, 0),
		0.1f,
		25,
		PINK,
		CREAM
	};

	BouncingCircle* newCircle = new BouncingCircle("Circle " + this->CircleList.size() + 1, prop, true);
	this->CircleList.push_back(newCircle);
}

void AppWindow::onKeyDown(int key)
{
	switch (key) {
		case 'W':
			this->rotX += 0.707f * deltaTime;
			break;
		case 'S':
			this->rotX -= 0.707f * deltaTime;
			break;
		case 'A':
			this->rotY += 0.707f * deltaTime;
			break;
		case 'D':
			this->rotY -= 0.707f * deltaTime;
			break;
		case 27: // Escape
			exit(0);
			break;

	}
}

void AppWindow::onKeyUp(int key)
{
	switch (key) {
		case ' ': // Spacebar
			this->createCircle();
			break;
		case 8: // Backspace
			if (this->CircleList.size() > 0)
				this->CircleList.pop_back();
			else
				std::cout << "No existing circles." << std::endl;

			break;
		case 46: // Delete
			if (this->CircleList.size() > 0)
				this->CircleList.clear();
			else
				std::cout << "No existing circles." << std::endl;

			break;
	}
}

void AppWindow::onMouseMove(const Point& deltaMousePos)
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
