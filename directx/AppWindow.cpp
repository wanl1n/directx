#include "AppWindow.h"

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
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->m_swap_chain->release();
	GraphicsEngine::get()->release();
}
