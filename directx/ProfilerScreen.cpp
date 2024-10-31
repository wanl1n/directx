#include "ProfilerScreen.h"

ProfilerScreen::ProfilerScreen() : UIScreen("Profiler Screen") {}
ProfilerScreen::~ProfilerScreen() {}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Profiler", &isActive);

	ImGui::Text("%f ms/frame, %f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}
