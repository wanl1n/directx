#pragma once
#include "UIScreen.h"
#include "Constants.h"

class MenuScreen : public UIScreen
{
	private:
		bool showPopUp = false;

	public:
		MenuScreen();
		~MenuScreen();

		void drawUI();
};

