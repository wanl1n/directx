#include "SceneToolsScreen.h"
#include "AppWindow.h"

SceneToolsScreen::SceneToolsScreen() : UIScreen("Profiler Screen") {}
SceneToolsScreen::~SceneToolsScreen() {}

void SceneToolsScreen::drawUI()
{
	ImGui::Begin("Scene Tools", &isActive, ImGuiWindowFlags_NoTitleBar);

	if (AppWindow::getInstance()->getPlaying()) {
		if (this->buttonCentered("Stop")) {
			// Stop Game
			AppWindow::getInstance()->setPlaying(false);
		}
	}
	else {
		if (this->buttonCentered("Play")) {
			// Start Game Simulation
			AppWindow::getInstance()->setPlaying(true);
		}
	}

	ImGui::End();
}
