#pragma once
#include "Windows.h"
#include "UINames.h"
#include "UIInclude.h"

#include "Constants.h"
#include "RenderSystem.h"

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

	private:
		void setUIStyle();
};

