#include "ProfilerScreen.h"

ProfilerScreen::ProfilerScreen() : UIScreen("Profiler Screen") {}
ProfilerScreen::~ProfilerScreen() {}

void ProfilerScreen::drawUI()
{
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Sample", &isActive, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Credits", "Ctrl+O")) {  }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { isActive = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Edit a color stored as 4 floats
	float pink[] = { 0.957f, 0.761f, 0.761f, 1.0f };
	ImGui::ColorEdit4("Color", pink);

	// Generate samples and plot them
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 150.0f / 255.0f, 200.0f / 255.0f, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();
}
