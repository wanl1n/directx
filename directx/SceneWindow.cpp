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

void SceneWindow::onCreate()
{
	Window::onCreate();
}

void SceneWindow::onUpdate()
{
	Window::onUpdate();

	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, PINK);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 3. Update Game Objects.
	for (Quad* obj : this->QuadList)
		obj->update(deltaTime, this->getClientWindowRect());
	for (Cube* obj : this->CubeList)
		obj->update(deltaTime, this->getClientWindowRect());
	for (Circle* obj : this->CircleList)
		obj->update(deltaTime, this->getClientWindowRect());

	this->grid->draw();

	for (Quad* obj : this->QuadList)
		obj->draw();
	for (Cube* obj : this->CubeList)
		obj->draw();
	for (Circle* obj : this->CircleList)
		obj->draw();

	this->swapChain->present(true);

	deltaTime = EngineTime::getDeltaTime();
}

void SceneWindow::onDestroy()
{
	Window::onDestroy();

	for (Quad* gameObject : QuadList) {
		if (gameObject) gameObject->release();
	}
	for (Cube* gameObject : CubeList) {
		if (gameObject) gameObject->release();
	}

	this->swapChain->release();
	GraphicsEngine::get()->release();
}

void SceneWindow::initializeEngine()
{
	EngineTime::initialize();
	// Input System
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(SceneWindow::getInstance());

	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	DeviceContext* device = graphicsEngine->getImmediateDeviceContext();

	this->swapChain = graphicsEngine->createSwapChain();

	RECT windowRect = this->getClientWindowRect();
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	this->swapChain->init(this->hwnd, width, height);

	//this->createQuads();
	this->createCubes();

	this->grid = new Grid("Grid", true);
}

void SceneWindow::createQuads()
{
	QuadVertices pos1 = { Vector3(-0.5f, -0.5f, 1.0f),
						Vector3(-0.5f, 0.5f, 1.0f),
						Vector3(0.5f, -0.5f, 1.0f),
						Vector3(0.5f, 0.5f, 1.0f) };
	QuadVertices pos2 = { Vector3(-0.6f, -0.2f, 1.0f),
						Vector3(-0.4f, 0.5f, 1.0f),
						Vector3(0.6f, -0.3f, 1.0f),
						Vector3(0.1f, 0.5f, 1.0f) };
	QuadVertices pos3 = { Vector3(-0.9f, -0.6f, 1.0f),
						Vector3(-0.9f, 0.6f, 1.0f),
						Vector3(-0.6f, -0.4f, 1.0f),
						Vector3(-0.6f, 0.4f, 1.0f) };
	QuadVertices pos4 = { Vector3(0.6f, -0.2f, 1.0f),
						Vector3(0.6f, 0.5f, 1.0f),
						Vector3(0.9f, -0.3f, 1.0f),
						Vector3(0.9f, 0.5f, 1.0f) };
	QuadColors color1 = { CREAM, LAVENDER, CREAM, LAVENDER };
	QuadColors color2 = { SPACE, MATCHA, CREAM, LAVENDER };
	QuadColors color3 = { LAVENDER, LAVENDER, CREAM, CREAM };
	QuadColors color4 = { SPACE, SPACE, LAVENDER, LAVENDER };
	QuadColors trans = { CLEAR, CLEAR, CLEAR, CLEAR };
	QuadProps quadProps1 = { pos1, pos2, color2, trans };
	QuadProps quadProps2 = { pos3, pos2, color2, trans };
	QuadProps quadProps3 = { pos4, pos2, color2, trans };

	Quad* quad1 = new Quad("Quad 1", quadProps1, true);
	this->QuadList.push_back(quad1);

	//PulsingQuad* quad2 = new PulsingQuad("My heartbeat", shaderByteCode, sizeShader, quadProps2, true);
	//this->QuadList.push_back(quad2);

	//Area51* quad3 = new Area51("Area 51", shaderByteCode, sizeShader, quadProps3, true);
	//this->QuadList.push_back(quad3);
}

void SceneWindow::createCubes()
{
	CubeVertex props = {
		Vector3(0),
		CREAM,
		LAVENDER
	};

	Cube* cube1 = new Cube("My First Cube", props, true);
	this->CubeList.push_back(cube1);
	
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


void SceneWindow::onKeyDown(int key)
{
	//std::cout << "Key down." << std::endl;
	switch (key) {
		case 27: // Escape
			exit(0);
			break;
	}
	//std::cout << key << std::endl;
}

void SceneWindow::onKeyUp(int key)
{
	switch (key) {
		case ' ': // Spacebar
			this->createCubes();
			break;
		case 8: // Backspace
			this->CircleList.pop_back();
			break;
		case 46: // Delete
			this->CircleList.clear();
			break;
	}
}

void SceneWindow::onMouseMove(const Point& deltaMousePos)
{
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