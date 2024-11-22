#include "MenuScreen.h"

#include "GameObjectManager.h"
#include "UIManager.h"
#include "CameraManager.h"
#include "FileManager.h"

MenuScreen::MenuScreen() : UIScreen("Menu Screen") {}
MenuScreen::~MenuScreen() {}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "Ctrl+O")) {}
			if (ImGui::MenuItem("Save", "Ctrl+S")) 
			{
				FileManager::getInstance()->saveLevel();
				ImGui::OpenPopup("Confirm Save");
			}
			if (ImGui::MenuItem("Close", "Ctrl+W")) { isActive = false; }
			ImGui::EndMenu();

			if (ImGui::BeginPopup("Confirm Save")) {
				ImGui::Text("Save current level as \"Main Level.level\"?");
				if (buttonCentered("Save")) showPopUp = false;
				ImGui::EndPopup();
			}
		}

		if (ImGui::BeginMenu("Game Object"))
		{
			/*if (ImGui::BeginMenu("2D")) {
				if (ImGui::MenuItem("Quad", "")) { GameObjectManager::getInstance()->addGameObject(QUAD); }
				if (ImGui::MenuItem("Circle", "")) { GameObjectManager::getInstance()->addGameObject(CIRCLE); }

				ImGui::EndMenu();
			}*/
			if (ImGui::BeginMenu("3D")) {
				if (ImGui::BeginMenu("Cube")) {
					if (ImGui::MenuItem("Cube", "")) { GameObjectManager::getInstance()->addGameObject(CUBE); }
					//if (ImGui::MenuItem("Textured Cube", "")) { GameObjectManager::getInstance()->addGameObject(TEXTURED_CUBE); }
					//if (ImGui::MenuItem("Physics Cube", "")) { GameObjectManager::getInstance()->addGameObject(PHYSICS_CUBE); }
					//if (ImGui::MenuItem("Physics Cube (20)", "")) { GameObjectManager::getInstance()->addGameObject(PHYSICS_CUBE, 20); }
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Plane", "")) { GameObjectManager::getInstance()->addGameObject(PLANE); }
				if (ImGui::MenuItem("Sphere", "")) { GameObjectManager::getInstance()->addGameObject(SPHERE); }
				if (ImGui::MenuItem("Capsule", "")) { GameObjectManager::getInstance()->addGameObject(CAPSULE); }
				if (ImGui::MenuItem("Cylinder", "")) { GameObjectManager::getInstance()->addGameObject(CYLINDER); }

				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			UINames uiNames;
			if (ImGui::MenuItem("Hierarchy", "")) { UIManager::getInstance()->openWindow(HIERARCHY); }
			if (ImGui::MenuItem("Inspector", "")) { UIManager::getInstance()->openWindow(INSPECTOR); }
			if (ImGui::MenuItem("Profiler", "")) { UIManager::getInstance()->openWindow(PROFILER); }
			if (ImGui::MenuItem("Color Picker", "")) { UIManager::getInstance()->openWindow(COLOR_PICKER); }

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene Camera"))
		{
			UINames uiNames;
			if (ImGui::MenuItem("Orthographic", "")) { CameraManager::getInstance()->getActiveCamera()->setProjectionType(ORTHOGRAPHIC); }
			if (ImGui::MenuItem("Perspective", "")) { CameraManager::getInstance()->getActiveCamera()->setProjectionType(PERSPECTIVE); }
			if (ImGui::MenuItem("Top-down", "")) { CameraManager::getInstance()->getActiveCamera()->setProjectionType(TOPDOWN); }
			if (ImGui::MenuItem("Side-scroller", "")) { CameraManager::getInstance()->getActiveCamera()->setProjectionType(SIDESCROLLER); }

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("About"))
		{
			UINames uiNames;
			if (ImGui::MenuItem("Credits", "")) { UIManager::getInstance()->openWindow(CREDITS); }

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}
