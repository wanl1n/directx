#pragma once
#include "UIScreen.h"

class SceneToolsScreen : public UIScreen
{
private:
	bool play = false;
public:
	SceneToolsScreen();
	~SceneToolsScreen();

	void drawUI();
};

