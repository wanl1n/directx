#pragma once
#include "UIScreen.h"
#include "imgui-master/imgui_stdlib.h"

class InspectorScreen : public UIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();

	void drawUI();
};