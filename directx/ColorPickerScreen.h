#pragma once
#include "UIScreen.h"

class ColorPickerScreen : public UIScreen
{
	private:
		float color[4];

	public:
		ColorPickerScreen();
		~ColorPickerScreen();

		void drawUI();
};

