#include "UIScreen.h"

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
