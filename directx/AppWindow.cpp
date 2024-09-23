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

	QuadVertex pos1 = { Vector3(-0.5f, -0.5f, 0.0f),
						Vector3(-0.5f, 0.5f, 0.0f),
						Vector3(0.5f, -0.5f, 0.0f),
						Vector3(0.5f, 0.5f, 0.0f) };
	QuadVertex pos2 = { Vector3(-0.6f, -0.2f, 0.0f),
						Vector3(-0.4f, 0.5f, 0.0f),
						Vector3(0.6f, -0.3f, 0.0f),
						Vector3(0.1f, 0.5f, 0.0f) };
	QuadColor color1 = { CREAM, MATCHA, SPACE, LAVENDER };
	QuadColor color2 = { LAVENDER, CREAM, MATCHA, SPACE };
	QuadProps quadProps = { pos1, pos2, color1, color2 };

	Quad* quad = new Quad("CJ", shader_byte_code, size_shader, quadProps);
	this->GOList.push_back(quad);

	GraphicsEngine::get()->releaseCompiledShader();

	// Creating Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();
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

	//Testing
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount64() - m_old_time;

	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	// 3. Update Game Objects.
	for (Quad* obj : this->GOList) {
		obj->update(m_delta_time, this->getClientWindowRect(), this->m_vs, this->m_ps);
	}

	// 4. Set Shaders.
	device->setVertexShader(this->m_vs);
	device->setPixelShader(this->m_ps);

	// 5. Draw all Game Objects.
	for (int i = 0; i < this->GOList.size(); i++) {
		this->GOList[i]->draw(this->m_vs, this->m_ps);
	}

	this->m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
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
	GraphicsEngine::get()->release();
}

void AppWindow::updateTime()
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount64() - m_old_time;

	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount64();
	m_angle += 1.57f * m_delta_time;
}
