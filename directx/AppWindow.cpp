#include "AppWindow.h"
#include "Windows.h"
#include "Colors.h"
#include "Constant.h"

AppWindow::AppWindow() {}
AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	this->m_swap_chain->init(this->m_hwnd, rc.right-rc.left, rc.bottom-rc.top);

	// Shader Attributes
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Creating Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//					INITIAL CENTER POS		TARGET CENTER POS	COLOR
	Vertex leftPos =	{ -0.5f, 0.0f , 0.0f,	-0.6f, 0.5f, 0.0f,	CREAM };
	Vertex centerPos =	{ -0.1f, -0.1f , 0.0f,	0.1f, 0.1f, 0.0f,	MATCHA };
	Vertex rightPos =	{ 0.5f, 0.0f , 0.0f,	0.6f, -0.5f, 0.0f,	SPACE };

	Quad* quad1 = new Quad("Quad 1", shader_byte_code, size_shader, leftPos, 0.3f, 0.25f);
	this->GOList.push_back(quad1);

	Quad* quad2 = new Quad("Quad 2", shader_byte_code, size_shader, centerPos, 0.3f, 0.25f, CREAM, MATCHA);
	this->GOList.push_back(quad2);
	
	Quad* quad3 = new Quad("Quad 3", shader_byte_code, size_shader, rightPos, 0.3f, 0.25f, CREAM, MATCHA, SPACE, CREAM);
	this->GOList.push_back(quad3);

	GraphicsEngine::get()->releaseCompiledShader();

	// Creating Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	Constant cc = { 0 };

	this->m_cb = GraphicsEngine::get()->createConstantBuffer();
	this->m_cb->load(&cc, sizeof(Constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// 1. Clear Render Target.
	device->clearRenderTargetColor(this->m_swap_chain, 0.957f, 0.761f, 0.761, 1);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	device->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 3. Update Time counter.
	Constant cc;
	cc.m_time = ::GetTickCount64();
	this->m_cb->update(device, &cc);

	// 4. Bind Constant Buffer to Shaders.
	device->setConstantBuffer(this->m_vs, this->m_cb);
	device->setConstantBuffer(this->m_ps, this->m_cb);

	// 5. Set Shaders.
	device->setVertexShader(this->m_vs);
	device->setPixelShader(this->m_ps);

	// 6. Draw all Game Objects.
	for (int i = 0; i < this->GOList.size(); i++) {
		this->GOList[i]->draw(m_vs, m_ps);
	}

	this->m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	for (Quad* gameObject : GOList) {
		if (gameObject) gameObject->release();
	}

	this->m_swap_chain->release();
	this->m_vs->release();
	this->m_ps->release();
	this->m_cb->release();
	GraphicsEngine::get()->release();
}
