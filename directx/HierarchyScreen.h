#pragma once
#include "UIScreen.h"

class HierarchyScreen : public UIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();

	void drawUI();

	bool contains(String str, String substr);
};

