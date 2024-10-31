#pragma once
#include "Windows.h"
#include "UIInclude.h"
#include "ImGuiInclude.h"

#include "Constants.h"
#include "RenderSystem.h"

typedef std::string String;

class UINames {
public:
	typedef std::string String;
	const String PROFILER_SCREEN = "PROFILER SCREEN";
	const String MENU_SCREEN = "MENU SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY SCREEN";
	const String CREDITS_SCREEN = "CREDITS SCREEN";
};

class UIScreen;

class UIManager
{
	public:
		typedef std::string String;
		typedef std::vector<UIScreen*> UIScreenList;
		typedef std::unordered_map<String, UIScreen*> UIScreenTable;

		static UIManager* getInstance();
		static void initialize(HWND hwnd);
		static void destroy();

	private:
		UIScreenList list;
		UIScreenTable table;

		UIManager(HWND hwnd);
		~UIManager();
		UIManager(UIManager const&) {};
		UIManager& operator = (UIManager const&) {};
		static UIManager* sharedInstance;

	public:
		void update();
		void render();
		void openWindow(SCREENS screenName);

	private:
		void setUIStyle();
};

