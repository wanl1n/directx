#include "AppWindow.h"
#include "Windows.h"

#include "Colors.h"
#include "Constant.h"

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

	//Testing
	unsigned long new_time = 0;
	if (oldTime)
		new_time = ::GetTickCount64() - oldTime;

	deltaTime = new_time / 1000.0f;
	oldTime = ::GetTickCount();


	// 3. Update Game Objects.
	for (Quad* obj : this->GOList) {
		obj->update(deltaTime, this->getClientWindowRect(), this->vs, this->ps);
	}

	// 4. Set Shaders.
	device->setVertexShader(this->vs);
	device->setPixelShader(this->ps);

	// 5. Draw all Game Objects.
	for (int i = 0; i < this->GOList.size(); i++) {
		this->GOList[i]->draw(this->vs, this->ps);
	}

	this->swapChain->present(true);

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
	this->vs->release();
	this->ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	this->swapChain = graphicsEngine->createSwapChain();

	RECT windowRect = this->getClientWindowRect();
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	this->swapChain->init(this->hwnd, width, height);

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);

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
	QuadProps quadProps2 = { pos3, pos2, color2, color3 };
	QuadProps quadProps3 = { pos4, pos2, color3, color4 };

	Quad* quad1 = new Quad("Quad 1", shaderByteCode, sizeShader, quadProps1);
	//this->GOList.push_back(quad1);

	Quad* quad2 = new Quad("Quad 2", shaderByteCode, sizeShader, quadProps2);
	//this->GOList.push_back(quad2);

	Quad* quad3 = new Quad("Quad 3", shaderByteCode, sizeShader, quadProps3);
	this->GOList.push_back(quad3);

	graphicsEngine->releaseCompiledShader();

	// Creating Pixel Shader
	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();
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
