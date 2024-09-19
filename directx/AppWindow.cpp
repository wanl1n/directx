#include "AppWindow.h"

struct vec3 {
	float x, y, z;
};

struct vertex {
	vec3 position;
	vec3 color;
};

AppWindow::AppWindow() {}
AppWindow::~AppWindow() {}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	this->m_swap_chain->init(this->m_hwnd, rc.right-rc.left, rc.bottom-rc.top);

	/*this->m_quad = GameObject();
	this->m_quad.init(1);*/

	GameObject quad1 = GameObject();
	quad1.init(1);
	this->GOList.push_back(quad1);

	GameObject quad2 = GameObject();
	quad2.init(2);
	this->GOList.push_back(quad2);

	GameObject quad3 = GameObject();
	quad3.init(3);
	this->GOList.push_back(quad3);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	// 1. Clear Render Target.
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.957f, 0.761f, 0.761, 1);

	// 2. Set the target Viewport where we'll draw.
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (GameObject quad : this->GOList) {
		// 3. Set default shader in the graphics pipeline to be able to draw.
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(quad.getVS());
		GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(quad.getPS());

		// 4. Set the vertices of the triangle we want to draw.
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(quad.getVB());

		// 5. Draw the triangle.
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(quad.getVB()->getSizeVertexList(), 0);
		this->m_swap_chain->present(true);
	}

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->m_vb->release();
	this->m_swap_chain->release();
	this->m_vs->release();
	this->m_ps->release();
	GraphicsEngine::get()->release();
}
