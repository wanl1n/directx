#pragma once
#include <Windows.h>
#include "vector"
#include "Constants.h"

class EngineTime;

class Window {
	protected:
		HWND hwnd;
		std::vector<HWND> childWindows;

		bool running;
		std::vector<bool> windowRunning;
		bool initializing;

		float FPS = 60;
		float lastUpdatedTime = 0;

		bool showFPS = true;
		float fpsTimer = 0;
		float fpsCounter = 0;

	public:
		Window();
		~Window();
		void initialize();

		bool createChildWindow();
		bool broadcast();
		bool run();

		virtual void onCreate();
		virtual void onUpdate();
		virtual void onDestroy();
		virtual void onFocus();
		virtual void onKillFocus();

		RECT getClientWindowRect();
		RECT getChildWindowRect(int index);
		HWND getWindowHandle();

		friend class EngineTime;
};