#pragma once
#include <string>
#include "ImGuiInclude.h"

typedef std::string String;

class UIManager;

class UIScreen
{
	protected:
		typedef std::string String;

		bool isActive;
		String name;

		UIScreen(String name);
		~UIScreen();

		void textCentered(std::string text);
		bool buttonCentered(std::string text);
		void imageCentered(const wchar_t* path, float sizeMult = 1.0f);

		String getName();
		bool getActive();
		void setActive(bool active);
		virtual void drawUI() = 0;

		friend class UIManager;
};
