#include "Window.h"

#include "EngineTime.h"

Window::Window() {}
Window::~Window() {}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
		// Event when Window Created.
		case WM_CREATE:
		{
			// collected here..
			Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			// .. and then stored for later lookup
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
			window->setHWND(hwnd);
			window->onCreate();
			break;
		}

		// Event when Window Focused.
		case WM_SETFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onFocus();
			break;
		}

		// Event when Window Unfocused.
		case WM_KILLFOCUS:
		{
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onKillFocus();
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

bool Window::init(float width, float height)
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
		return false;
	
	hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "Kate's Game Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, NULL, this);
	
	if (!hwnd) return false;

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	this->running = true;

	return true;
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
			std::cout << "FPS: " << fpsCounter << std::endl;
			fpsCounter = 0;
		}
	}

	Sleep(1);
	EngineTime::LogFrameEnd();
	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(this->hwnd))
		return false;

	return true;
}

bool Window::isRunning()
{
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

void Window::setHWND(HWND hwnd)
{
	this->hwnd = hwnd;
}
