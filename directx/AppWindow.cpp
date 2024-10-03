#include "AppWindow.h"
#include "Windows.h"
#include "InputSystem.h"

#include "Constants.h"
#include "Constant.h"

AppWindow* AppWindow::sharedInstance = nullptr;
AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init(1024, 728);
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
	device->clearRenderTargetColor(this->swapChain, 0.957f, 0.761f, 0.761, 1);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 3. Update Game Objects.
	for (Quad* obj : this->GOList) 
		obj->update(deltaTime, this->getClientWindowRect());
	for (Cube* obj : this->CubeList)
		obj->update(deltaTime, this->getClientWindowRect(), Vector3(0), Vector3(this->rotX, this->rotY, 0.0f));

	// 4. Draw all Game Objects.
	for (Quad* obj : this->GOList)
		obj->draw();
	for (Cube* obj : this->CubeList)
		obj->draw();

	this->swapChain->present(true);

	// Update Delta time.
	oldDelta = newDelta;
	newDelta = ::GetTickCount();
	deltaTime = (oldDelta) ? ((newDelta - oldDelta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	for (Quad* gameObject : GOList) {
		if (gameObject) gameObject->release();
	}

	this->swapChain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::initializeEngine()
{
	// Input System
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(AppWindow::getInstance());

	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	this->swapChain = graphicsEngine->createSwapChain();

	RECT windowRect = this->getClientWindowRect();
	this->swapChain->init(this->hwnd, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	// Create Game OBjects.
	//this->createQuads();
	this->createCubes();
}

void AppWindow::updateTime()
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	unsigned long new_time = 0;
	if (oldTime)
		new_time = ::GetTickCount64() - oldTime;

	deltaTime = new_time / 1000.0f;
	oldTime = ::GetTickCount64();
}

void AppWindow::createQuads()
{
	QuadVertex pos1 = { Vector3(-0.5f, -0.5f, 1.0f),
						Vector3(-0.5f, 0.5f, 1.0f),
						Vector3(0.5f, -0.5f, 1.0f),
						Vector3(0.5f, 0.5f, 1.0f) };
	QuadVertex pos2 = { Vector3(-0.6f, -0.2f, 1.0f),
						Vector3(-0.4f, 0.5f, 1.0f),
						Vector3(0.6f, -0.3f, 1.0f),
						Vector3(0.1f, 0.5f, 1.0f) };
	QuadVertex pos3 = { Vector3(-0.9f, -0.6f, 1.0f),
						Vector3(-0.9f, 0.6f, 1.0f),
						Vector3(-0.6f, -0.4f, 1.0f),
						Vector3(-0.6f, 0.4f, 1.0f) };
	QuadVertex pos4 = { Vector3(0.6f, -0.2f, 1.0f),
						Vector3(0.6f, 0.5f, 1.0f),
						Vector3(0.9f, -0.3f, 1.0f),
						Vector3(0.9f, 0.5f, 1.0f) };
	QuadColor color1 = { CREAM, MATCHA, SPACE, LAVENDER };
	QuadColor color2 = { LAVENDER, CREAM, MATCHA, SPACE };
	QuadColor color3 = { LAVENDER, LAVENDER, MATCHA, MATCHA };
	QuadColor color4 = { CREAM, CREAM, SPACE, SPACE };
	QuadProps quadProps1 = { pos1, pos2, color1, color2 };
	QuadProps quadProps2 = { pos3, pos2, color2, color3 };
	QuadProps quadProps3 = { pos4, pos2, color3, color4 };

	Quad* quad1 = new Quad("Quad 1", quadProps1, false);
	this->GOList.push_back(quad1);

	Quad* quad2 = new Quad("Quad 2", quadProps2, false);
	this->GOList.push_back(quad2);

	Quad* quad3 = new Quad("Quad 3", quadProps3, false);
	this->GOList.push_back(quad3);
}

void AppWindow::createCubes()
{
	CubeVertex props = {
		Vector3(0),
		CREAM,
		LAVENDER
	};

	Cube* cube1 = new Cube("My First Cube", props, true);
	this->CubeList.push_back(cube1);

	RotatingCube* mefr = new RotatingCube("me when i rotate", props, true);
	this->CubeList.push_back(mefr);
}

void AppWindow::onKeyDown(int key)
{
	std::cout << "Key down." << std::endl;
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
	}
}

void AppWindow::onKeyUp(int key)
{
	std::cout << "Key up." << std::endl;
}
