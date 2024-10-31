#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "ImGuiInclude.h"

#include "Window.h"
#include "UIScreen.h"

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