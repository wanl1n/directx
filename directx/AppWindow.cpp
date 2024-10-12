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

	this->rotX += deltaTime;
	this->rotY += deltaTime;

	// 3. Update Game Objects.
	for (Quad* obj : this->GOList) 
		obj->update(deltaTime, rc);
	for (Cube* obj : this->CubeList)
		obj->update(deltaTime, rc, Vector3(0), Vector3(rotX, rotY, 0));
	//obj->update(deltaTime, rc, Vector3(0), Vector3(this->rotX, this->rotY, 0.0f), Vector3(this->scaler));
	for (Circle* obj : this->CircleList)
		obj->update(deltaTime, rc);

	// 4. Draw all Game Objects.
	for (Quad* obj : this->GOList)
		obj->draw();
	for (Cube* obj : this->CubeList)
		obj->draw();
	for (Circle* obj : this->CircleList)
		obj->draw();

	this->swapChain->present(true);

	// Update Delta time.
	deltaTime = EngineTime::getDeltaTime();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	for (Quad* gameObject : GOList) {
		if (gameObject) gameObject->release();
	}
	for (Quad* gameObject : QuadList) {
		if (gameObject) gameObject->release();
	}
	for (Circle* gameObject : CircleList) {
		if (gameObject) gameObject->release();
	}
	for (Cube* gameObject : CubeList) {
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

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	// Create 100 cubes in random positions
	for (int i = 0; i < 100; i++) {
		this->createRotatingCube();
	}
}

void AppWindow::createQuad()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::cout << "Creating Quad." << std::endl;
	float radius = 0.1f;
	int min = -1 + radius * 2;
	int max = 1 - radius * 2;

	float posX = min + (std::rand() % (max - min + 1));
	float posY = min + (std::rand() % (max - min + 1));

	// left top right bottom
	Rect pts = {posX - radius, posY + radius, posX + radius, posY - radius};

	QuadVertex pos1 = { Vector3(pts.left, pts.bottom, 1.0f),
						Vector3(pts.left, pts.top, 1.0f),
						Vector3(pts.right, pts.bottom, 1.0f),
						Vector3(pts.right, pts.top, 1.0f) };
	
	QuadColor color1 = { CREAM, MATCHA, SPACE, LAVENDER };
	QuadColor color2 = { LAVENDER, CREAM, MATCHA, SPACE };
	QuadProps quadProps1 = { pos1, pos1, color1, color2 };

	Area51* quad1 = new Area51("Generic Quad", quadProps1, false);
	this->GOList.push_back(quad1);
}

void AppWindow::createCircle()
{
	//std::cout << "Creating Circle." << std::endl;
	CircleProps prop = {
		Vector3(0, 0, 0),
		0.1f,
		25,
		PINK,
		CREAM
	};

	BouncingCircle* newCircle = new BouncingCircle("pls work", prop, true);
	//Circle* newCircle = new Circle("pls work", prop, true);
	this->CircleList.push_back(newCircle);
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

	/*Quad* quad2 = new Quad("Quad 2", quadProps2, false);
	this->GOList.push_back(quad2);

	Quad* quad3 = new Quad("Quad 3", quadProps3, false);
	this->GOList.push_back(quad3);*/
}

void AppWindow::createCube()
{
	CubeVertex props = {
		Vector3(1),
		CREAM,
		LAVENDER
	};

	Cube* cube1 = new Cube("My First Cube", props, true);
	this->CubeList.push_back(cube1);
}

void AppWindow::createRotatingCube()
{
	CubeVertex props = {
		Vector3(1),
		CREAM,
		LAVENDER
	};

	RotatingCube* mefr = new RotatingCube("me when i rotate", props, true);
	this->CubeList.push_back(mefr);
}

void AppWindow::onKeyDown(int key)
{
	//std::cout << "Key down." << std::endl;
	//switch (key) {
	//	case 'W':
	//		this->rotX += 0.707f * deltaTime;
	//		break;
	//	case 'S':
	//		this->rotX -= 0.707f * deltaTime;
	//		break;
	//	case 'A':
	//		this->rotY += 0.707f * deltaTime;
	//		break;
	//	case 'D':
	//		this->rotY -= 0.707f * deltaTime;
	//		break;
	//	case 27: // Escape
	//		exit(0);
	//		break;

	//}
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

void AppWindow::onMouseMove(const Point& deltaMousePos)
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
