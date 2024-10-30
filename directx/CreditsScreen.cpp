#include "CreditsScreen.h"

CreditsScreen::CreditsScreen() : UIScreen("Credits Screen") {}
CreditsScreen::~CreditsScreen() {}

void CreditsScreen::drawUI()
{
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("About", &isActive, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Sample", "Ctrl+O")) { }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { isActive = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("Scene Editor v0.01");
	ImGui::Text("Developed by: Kate Nicole Young");
	ImGui::Text("");
	ImGui::Text("Acknowledgements");
	ImGui::Text("Doc Neil Del Gallego as Professor");
	ImGui::Text("Omar Cornut as Dear ImGui Developer");
	ImGui::Text("Patitotective as ImThemes Developer");
	ImGui::Text("");
	ImGui::Text("Special Thanks");
	ImGui::Text("My Parents as Financial Support");

	if (this->buttonCentered("Close")) isActive = false;

	ImGui::End();
}
