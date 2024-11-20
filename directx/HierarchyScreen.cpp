#include "HierarchyScreen.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "GameObjectManager.h"

HierarchyScreen::HierarchyScreen() : UIScreen("Hierarchy Screen") {}
HierarchyScreen::~HierarchyScreen() {}

void HierarchyScreen::drawUI()
{
	ImGui::Begin("Hierarchy", &isActive);
	
	String query = "";
	static char searchQuery[128] = "";
	ImGui::InputTextWithHint("Search", "Enter Game Object name.", searchQuery, IM_ARRAYSIZE(searchQuery));
	query = searchQuery;

	std::vector<GameObject*> objList = GameObjectManager::getInstance()->getGameObjects();

	for (GameObject* obj : objList)
	{
		String name = obj->getName();
		bool searchFound = name.find(query) != String::npos;
		searchFound = this->contains(name, query);

		if (searchFound)
		{
			if (ImGui::Button(name.c_str(), ImVec2(ImGui::GetWindowSize().x - 15, 20)))
				GameObjectManager::getInstance()->setSelectedGameObject(obj);
		}
	}

	ImGui::End();
}

bool HierarchyScreen::contains(String str, String substr)
{
	if (substr == "") return true;

	int strLen = str.length();
	int substrLen = substr.length();

	for (int i = 0; i <= strLen - substrLen; i++)
	{
		for (int j = 0; j < substrLen; j++)
		{
			if (tolower(str[i + j]) == tolower(substr[j]))
				return true;
		}
	}
	return false;
}

