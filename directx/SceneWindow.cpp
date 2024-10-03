#include "SceneWindow.h"
#include "Windows.h"

#include "Constants.h"
#include "Constant.h"

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
	if (this->QuadList.size() > 0) {
		std::cout << "Updating Quads." << std::endl;
		for (Quad* obj : this->QuadList)
			obj->update(deltaTime, this->getClientWindowRect());
	}
	if (this->CubeList.size() > 0) {
		std::cout << "Updating Cubes." << std::endl;
		for (Cube* obj : this->CubeList)
			obj->update(deltaTime, this->getClientWindowRect());
	}

	std::cout << "Drawing Grid." << std::endl;
	this->grid->draw();

	// 4. Draw all Game Objects.
	if (this->QuadList.size() > 0) {
		std::cout << "Drawing Quads." << std::endl;
		for (Quad* obj : this->QuadList)
			obj->draw();
	}
	/*if (this->CubeList.size() > 0) {
		std::cout << "Drawing Cubes." << std::endl;
		for (Cube* obj : this->CubeList)
			obj->draw();
	}*/

	this->swapChain->present(true);

	// Update Delta time.
	oldDelta = newDelta;
	newDelta = ::GetTickCount64();
	deltaTime = (oldDelta) ? ((newDelta - oldDelta) / 1000.0f) : 0;
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
	this->vs->release();
	this->ps->release();
	GraphicsEngine::get()->release();
}

void SceneWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	DeviceContext* device = graphicsEngine->getImmediateDeviceContext();

	this->swapChain = graphicsEngine->createSwapChain();

	RECT windowRect = this->getClientWindowRect();
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	this->swapChain->init(this->hwnd, width, height);

	this->createQuads();
	this->createCubes();

	graphicsEngine->releaseCompiledShader();

	this->grid = new Grid("Grid", true);
}

void SceneWindow::updateTime()
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	unsigned long new_time = 0;
	if (oldTime)
		new_time = ::GetTickCount64() - oldTime;

	deltaTime = new_time / 1000.0f;
	oldTime = ::GetTickCount64();
}

void SceneWindow::createQuads()
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
	QuadColor color1 = { CREAM, LAVENDER, CREAM, LAVENDER };
	QuadColor color2 = { SPACE, MATCHA, CREAM, LAVENDER };
	QuadColor color3 = { LAVENDER, LAVENDER, CREAM, CREAM };
	QuadColor color4 = { SPACE, SPACE, LAVENDER, LAVENDER };
	QuadColor trans = { CLEAR, CLEAR, CLEAR, CLEAR };
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
}
