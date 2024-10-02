#pragma once
#include <Windows.h>
#include "vector"

class Window {
	protected:
		HWND hwnd;
		std::vector<HWND> childWindows;

		bool running;
		std::vector<bool> windowRunning;

	public:
		Window();
		~Window();

		bool init(float width, float height);
		bool createChildWindow();
		bool broadcast();
		bool release();
		bool isRunning();

		virtual void onCreate();
		virtual void onUpdate();
		virtual void onDestroy();

		RECT getClientWindowRect();
		RECT getChildWindowRect(int index);
		HWND getWindowHandle();
		void setHWND(HWND hwnd);
}; 