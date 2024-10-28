#pragma once
#include "Constants.h"
#include "Windows.h"
#include "RenderSystem.h"

#include "imgui-master/imgui.h"
#include "imgui-master/imgui_impl_win32.h"
#include "imgui-master/imgui_impl_dx11.h"

class UIManager
{
	public:
		static UIManager* getInstance();
		static void initialize(HWND hwnd, RenderSystem* rs);
		static void destroy();

	private:
		bool creditsOpen = true;
		bool demoOpen = true;

		UIManager();
		~UIManager();
		UIManager(UIManager const&) {};
		UIManager& operator = (UIManager const&) {};
		static UIManager* sharedInstance;

	public:
		void update();
		void render();
		void drawSampleUI();
		void drawCreditsUI();
		bool buttonCentered(std::string text);

	private:
		void setUIStyle();
};

