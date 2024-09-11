#include "AppWindow.h"

struct vec3 {
	float x, y, z;
};

struct vertex {
	vec3 position;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	this->m_swap_chain->init(this->m_hwnd, rc.right-rc.left, rc.bottom-rc.top);

	vertex list[] = {
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	// 1. Clear Render Target.
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.957f, 0.761f, 0.761, 1);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 3. Set default shader in the graphics pipeline to be able to draw.
	GraphicsEngine::get()->setShaders();

	// 4. Set the vertices of the triangle we want to draw.
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// 5. Draw the triangle.
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	this->m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->m_vb->release();
	this->m_swap_chain->release();
	GraphicsEngine::get()->release();
}
