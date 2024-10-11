#pragma once
#include <Windows.h>
#include "vector"

class EngineTime;

class Window {
	protected:
		HWND hwnd;
		std::vector<HWND> childWindows;

		bool running;
		std::vector<bool> windowRunning;

		float FPS = 60;
		float lastUpdatedTime = 0;

		bool showFPS = true;
		float fpsTimer = 0;
		float fpsCounter = 0;

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
		virtual void onFocus();
		virtual void onKillFocus();

		RECT getClientWindowRect();
		RECT getChildWindowRect(int index);
		HWND getWindowHandle();
		void setHWND(HWND hwnd);

		friend class EngineTime;
};