#include "InspectorScreen.h"

#include "GameObjectManager.h"

InspectorScreen::InspectorScreen() : UIScreen("Inspector Screen") {}
InspectorScreen::~InspectorScreen() {}

void InspectorScreen::drawUI()
{
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Inspector", &isActive);
	
	GameObject* obj = GameObjectManager::getInstance()->getSelectedGameObject();
	
	if (obj != NULL)
	{
		std::string name = obj->getName();
		if (ImGui::InputText("Name", &name))
		{
			obj->setName(name);
		}

		bool isActive = obj->getActive();
		if (ImGui::Checkbox("Active", &isActive))
		{
			obj->setActive(isActive);
		}

		Vector3 pos = obj->getPosition();
		float finalPos[] = { pos.x, pos.y, pos.z };
		if (ImGui::DragFloat3("Position", finalPos, 0.01f))
		{
			obj->setPosition(finalPos[0], finalPos[1], finalPos[2]);
		}

		Vector3 scale = obj->getScale();
		float finalScale[] = { scale.x, scale.y, scale.z };
		if (ImGui::DragFloat3("Scale", finalScale, 0.01f))
		{
			obj->setScale(Vector3(finalScale[0], finalScale[1], finalScale[2]));
		}

		Vector3 rot = obj->getRotation();
		float finalRot[] = { rot.x, rot.y, rot.z };
		if (ImGui::DragFloat3("Rotation", finalRot, 0.01f))
		{
			obj->setRotation(Vector3(finalRot[0], finalRot[1], finalRot[2]));
		}

		if (ImGui::Button("Delete", ImVec2(ImGui::GetWindowSize().x - 15, 20)))
		{
			GameObjectManager::getInstance()->resetSelection();
			GameObjectManager::getInstance()->removeGameObject(obj);
		}
	}
	ImGui::End();
}
