#include "Window.h"
#include <exception>
#include "EngineTime.h"
#include "imgui-master/imgui_impl_win32.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg) {
		// Event when Window Created.
	case WM_CREATE:
	{
		break;
	}

	// Event when Window Focused.
	case WM_SETFOCUS:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (window) window->onFocus();
		break;
	}

	// Event when Window Unfocused.
	case WM_KILLFOCUS:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (window) window->onKillFocus();
		break;
	}

	// Event when Window Destroyed.
	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

Window::Window() : width(1024), height(1024), initializing(true)
{
	this->initialize();
}

Window::Window(float width, float height) :
	width(width), height(height), initializing(true)
{
	this->initialize();
}

Window::~Window() {}

void Window::initialize()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		throw std::exception("Window creation failed.");

	hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass",
		"Kate's Game Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, width, height, NULL, NULL, NULL, NULL);

	if (!hwnd) throw std::exception("Window creation failed.");

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	this->running = true;
}

bool Window::createChildWindow() {
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "InspectorWindow";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	HWND window = ::CreateWindowEx(WS_EX_PALETTEWINDOW, "InspectorWindow", "Inspector", WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT, 300, 720, this->hwnd, NULL, NULL, this);

	if (!window) return false;

	::ShowWindow(window, SW_SHOW);
	::UpdateWindow(window);

	this->childWindows.push_back(window);
	this->windowRunning.push_back(true);

	return true;
}

bool Window::broadcast()
{
	if (this->initializing) {
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->onCreate();

		initializing = false;
	}

	EngineTime::LogFrameStart();
	MSG msg;

	float timePerFrame = 1.0f / FPS;
	this->lastUpdatedTime += EngineTime::getDeltaTime();

	if (this->lastUpdatedTime > timePerFrame) {
		this->lastUpdatedTime -= timePerFrame;
		this->onUpdate();
		
		fpsCounter++;
	}

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (showFPS) {
		float timeElapsed = GetTickCount64();
		fpsTimer += EngineTime::getDeltaTime();

		if (fpsTimer >= 1) {
			fpsTimer--;
			//std::cout << "FPS: " << fpsCounter << std::endl;
			fpsCounter = 0;
		}
	}

	Sleep(1);
	EngineTime::LogFrameEnd();
	return true;
}

bool Window::run()
{
	if (this->running)
		this->broadcast();

	return this->running;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	this->running = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->hwnd, &rc);
	return rc;
}

RECT Window::getChildWindowRect(int index)
{
	RECT rc;
	::GetClientRect(this->childWindows[index], &rc);
	return rc;
}

HWND Window::getWindowHandle()
{
	return this->hwnd;
}