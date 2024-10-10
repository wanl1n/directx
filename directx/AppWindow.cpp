#include "AppWindow.h"
#include "Windows.h"

#include "Colors.h"
#include "Constant.h"

#include "EngineTime.h"

AppWindow* AppWindow::sharedInstance = nullptr;
AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
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

	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->swapChain, 0.957f, 0.761f, 0.761, 1);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	deltaTime = EngineTime::getDeltaTime();

	// 3. Update Game Objects.
	for (Quad* obj : this->GOList) {
		obj->update(deltaTime, this->getClientWindowRect());
	}
	
	// 5. Draw all Game Objects.
	for (int i = 0; i < this->GOList.size(); i++) {
		this->GOList[i]->draw();
	}

	this->swapChain->present(true);
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
	EngineTime::initialize();

	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	this->swapChain = graphicsEngine->createSwapChain();

	RECT windowRect = this->getClientWindowRect();
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	this->swapChain->init(this->hwnd, width, height);

	this->createQuads();
}

void AppWindow::createQuads()
{
	QuadVertex pos1 = { Vector3(-0.5f, -0.5f, 0.0f),
						Vector3(-0.5f, 0.5f, 0.0f),
						Vector3(0.5f, -0.5f, 0.0f),
						Vector3(0.5f, 0.5f, 0.0f) };
	QuadVertex pos2 = { Vector3(-0.6f, -0.2f, 0.0f),
						Vector3(-0.4f, 0.5f, 0.0f),
						Vector3(0.6f, -0.3f, 0.0f),
						Vector3(-0.6f, -0.2f, 0.0f) };
	QuadVertex pos3 = { Vector3(-0.9f, -0.6f, 0.0f),
						Vector3(-0.9f, 0.6f, 0.0f),
						Vector3(-0.6f, -0.4f, 0.0f),
						Vector3(-0.6f, 0.4f, 0.0f) };
	QuadVertex pos4 = { Vector3(-0.2f, -0.2f, 0.0f),
						Vector3(-0.2f, 0.5f, 0.0f),
						Vector3(0.7f, -0.3f, 0.0f),
						Vector3(0.7f, 0.5f, 0.0f) };
	QuadColor color1 = { CREAM, MATCHA, SPACE, LAVENDER };
	QuadColor color2 = { LAVENDER, CREAM, MATCHA, SPACE };
	QuadColor color3 = { LAVENDER, LAVENDER, MATCHA, MATCHA };
	QuadColor color4 = { CREAM, CREAM, SPACE, SPACE };
	QuadProps quadProps1 = { pos1, pos2, color1, color2 };
	QuadProps quadProps2 = { pos3, pos1, color2, color3 };
	QuadProps quadProps3 = { pos4, pos2, color3, color4 };

	Quad* quad1 = new Quad("Quad 1", quadProps1);
	//this->GOList.push_back(quad1);

	Quad* quad2 = new Quad("Quad 2", quadProps2);
	this->GOList.push_back(quad2);

	Quad* quad3 = new Quad("Quad 3", quadProps3);
	this->GOList.push_back(quad3);
}
