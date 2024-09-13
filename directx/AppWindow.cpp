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

	vertex list1[] = {
		// Triangle List
		/*{ -0.5f, -0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },

		{ 0.5f, 0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f }*/

		// Triangle Strip
		/*{ -0.5f, -0.5f, 0.0f,	1, 0, 0 },
		{ -0.5f, 0.5f, 0.0f,	0, 1, 0 },
		{ 0.5f, -0.5f, 0.0f,	0, 0, 1 },
		{ 0.5f, 0.5f, 0.0f,		1, 1, 0 }*/

		// 1. Rainbow Rectangle
		{ -0.95f, -0.25f, 0.0f,	1, 0, 0 },
		{ -0.95f, 0.25f, 0.0f,	0, 1, 0 },
		{ -0.4f, -0.25f, 0.0f,	0, 0, 1 },
		{ -0.4f, 0.25f, 0.0f,	1, 1, 0 }
	};

	// 2. Rainbow Triangle
	vertex list2[] = {
		{ -0.3f, -0.25f, 0.0f,	1, 0, 0 },
		{ 0.0f, 0.25f, 0.0f,	0, 1, 0 },
		{ 0.3f, -0.25f, 0.0f,	0, 0, 1 }
	};

	// 3. Green Rectangle
	vertex list3[] = {
		{ 0.4f, -0.25f, 0.0f,	0, 1, 0 },
		{ 0.4f, 0.25f, 0.0f,	0, 1, 0 },
		{ 0.95f, -0.25f, 0.0f,	0, 1, 0 },
		{ 0.95f, 0.25f, 0.0f,	0, 1, 0 }
	};

	this->m_vb_rr = GraphicsEngine::get()->createVertexBuffer();
	this->m_vb_rt = GraphicsEngine::get()->createVertexBuffer();
	this->m_vb_gr = GraphicsEngine::get()->createVertexBuffer();

	UINT size_list_rectangle = ARRAYSIZE(list1);
	UINT size_list_triangle = ARRAYSIZE(list2);

	// Shader Attributes
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Creating Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	this->m_vb_rr->load(list1, sizeof(vertex), size_list_rectangle, shader_byte_code, size_shader);
	this->m_vb_rt->load(list2, sizeof(vertex), size_list_triangle, shader_byte_code, size_shader);
	this->m_vb_gr->load(list3, sizeof(vertex), size_list_rectangle, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	// Creating Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();
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
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	// 4. Set the vertices of the triangle we want to draw.
	// 5. Draw the triangle.
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb_rr);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb_rr->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb_rt);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb_rt->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb_gr);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb_gr->getSizeVertexList(), 0);

	this->m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->m_vb_rr->release();
	this->m_vb_rt->release();
	this->m_vb_gr->release();
	this->m_swap_chain->release();
	this->m_vs->release();
	this->m_ps->release();
	GraphicsEngine::get()->release();
}
