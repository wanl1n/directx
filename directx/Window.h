#pragma once
#include <Windows.h>

class EngineTime;

class Window {
	protected:
		HWND hwnd;
		bool running;

	public:
		Window();
		~Window();

		bool init();
		bool broadcast();
		bool release();
		bool isRunning();

		virtual void onCreate();
		virtual void onUpdate();
		virtual void onDestroy();

		RECT getClientWindowRect();
		HWND getWindowHandle();
		void setHWND(HWND hwnd);

		friend class EngineTime;
}; 