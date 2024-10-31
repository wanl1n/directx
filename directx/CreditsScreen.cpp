#include "CreditsScreen.h"

#include "TextureManager.h"

CreditsScreen::CreditsScreen() : UIScreen("Credits Screen") {}
CreditsScreen::~CreditsScreen() {}

void CreditsScreen::drawUI()
{
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Credits", &isActive);

	TextureNames txtNames;
	TextureData logo = TextureManager::getInstance()->getTexture(txtNames.LOGO);
	ImGui::Image((ImTextureID)(intptr_t)logo.texture, ImVec2(logo.width/5, logo.height/5));

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
