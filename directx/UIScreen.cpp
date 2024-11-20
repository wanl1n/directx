#include "UIScreen.h"

#include "Constants.h"
#include "GraphicsEngine.h"

#include "Texture.h"

UIScreen::UIScreen(String name) : isActive(true), name(name){}
UIScreen::~UIScreen() {}

void UIScreen::textCentered(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}

bool UIScreen::buttonCentered(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	return ImGui::Button(text.c_str());
}

void UIScreen::imageCentered(const wchar_t* path, float sizeMult)
{
	// Get Texture
	TexturePtr texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(path);
	
	// Calculate left padding
	ImVec2 imageSize = ImVec2(texture->getWidth() * sizeMult, texture->getHeight() * sizeMult);
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 padding = { (windowSize.x - imageSize.x) * 0.5f, ImGui::GetCursorPosY() };
	ImGui::SetCursorPos(padding);

	ImGui::Image((ImTextureID)(intptr_t)texture->getShaderResView(), imageSize);
}

String UIScreen::getName()
{
	return this->name;
}

bool UIScreen::getActive()
{
	return this->isActive;
}

void UIScreen::setActive(bool active)
{
	this->isActive = active;
}
