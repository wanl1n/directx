#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen() : UIScreen("Color Picker Screen")
{
    this->color[0] = 1.0f; 
    this->color[1] = 0.58f; 
    this->color[2] = 0.78f; 
    this->color[3] = 1.0f;
}
ColorPickerScreen::~ColorPickerScreen() {}

void ColorPickerScreen::drawUI()
{
    ImGui::Begin("Color Picker", &isActive);

    ImGui::ColorPicker4("Color", color, ImGuiColorEditFlags_PickerHueWheel);

    ImGui::End();
}
