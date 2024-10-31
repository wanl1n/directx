#include "CreditsScreen.h"

#include "TextureManager.h"

CreditsScreen::CreditsScreen() : UIScreen("Credits Screen") {}
CreditsScreen::~CreditsScreen() {}

void CreditsScreen::drawUI()
{
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Credits", &isActive);

	TextureNames txtNames;
	this->imageCentered(txtNames.LOGO, 0.2f);

	ImGui::Text("Scene Editor v0.01");
	ImGui::Text("Developed by: Kate Nicole Young");
	ImGui::Text("");
	ImGui::Text("Acknowledgements");
	ImGui::Text("GDENG03 Professor Doc Neil Del Gallego");
	ImGui::Text("Parcode C++ Game Engine Development");
	ImGui::Text("Dear ImGui Developer Omar Cornut");
	ImGui::Text("ImThemes Developer Patitotective");
	ImGui::Text("");
	ImGui::Text("Special Thanks");
	ImGui::Text("My Parents as Financial Support");

	if (this->buttonCentered("Close")) isActive = false;

	ImGui::End();
}
