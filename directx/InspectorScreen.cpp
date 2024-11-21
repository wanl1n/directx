#include "InspectorScreen.h"

#include "GameObjectManager.h"
#include "PhysicsComponent.h"

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

		Math::Vector3 pos = obj->getPosition();
		float finalPos[] = { pos.x, pos.y, pos.z };
		if (ImGui::DragFloat3("Position", finalPos, 0.01f))
		{
			obj->setPosition(finalPos[0], finalPos[1], finalPos[2]);
		}

		Math::Vector3 scale = obj->getScale();
		float finalScale[] = { scale.x, scale.y, scale.z };
		if (ImGui::DragFloat3("Scale", finalScale, 0.01f))
		{
			obj->setScale(Math::Vector3(finalScale[0], finalScale[1], finalScale[2]));
		}

		Math::Vector3 rot = obj->getRotation();
		float finalRot[] = { rot.x, rot.y, rot.z };
		if (ImGui::DragFloat3("Rotation", finalRot, 0.01f))
		{
			obj->setRotation(Math::Vector3(finalRot[0], finalRot[1], finalRot[2]));
		}

		if (ImGui::Button("Delete", ImVec2(ImGui::GetWindowSize().x - 15, 20)))
		{
			GameObjectManager::getInstance()->resetSelection();
			GameObjectManager::getInstance()->removeGameObject(obj);
		}

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		bool hasRigidbody = false;
		std::vector<Component*> components = obj->getAllComponents();
		for (Component* comp : components) {
			
			// Physics Checker
			if (comp->getType() == Component::ComponentType::Physics) hasRigidbody = true;

			if (ImGui::CollapsingHeader(comp->getName().c_str())) {
				
				// Physics Component
				if (comp->getType() == Component::ComponentType::Physics) {
					PhysicsComponent* pc = (PhysicsComponent*)comp;

					if (pc != NULL) {
						hasRigidbody = true;

						// Body Type
						std::string type = pc->getRBType();
						std::string bodyTypes[] = { "Dynamic", "Kinematic" };
						// Get current body type index;
						int currentBodyType = 0;
						for (int i = 0; i < bodyTypes->size(); i++) {
							if (type == bodyTypes[i]) currentBodyType = i;
						}
						// Body Type Dropdown
						if (ImGui::BeginCombo("Body Type", bodyTypes[currentBodyType].c_str())) // The second parameter is the label previewed before opening the combo.
						{
							for (int i = 0; i < IM_ARRAYSIZE(bodyTypes); i++)
							{
								bool selected = (bodyTypes[currentBodyType] == bodyTypes[i]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(bodyTypes[i].c_str(), selected))
									currentBodyType = i;
									if (selected)
										ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
							}
							ImGui::EndCombo();
						}
						pc->setRBType(bodyTypes[currentBodyType]);

						// Mass
						float mass = pc->getMass();
						if (ImGui::DragFloat("Mass", &mass, 0.01f)) 
							pc->setMass(mass);

						// Gravity
						bool gravityOn = pc->isGravityOn();
						ImGui::Checkbox("Gravity", &gravityOn);
						pc->setGravityOn(gravityOn);

						// Lock Position
						ImGui::Text("Lock Position");
						reactphysics3d::Vector3 lockPos = pc->getRigidBody()->getLinearLockAxisFactor();
						bool lockPosX = !(bool)lockPos.x;
						bool lockPosY = !(bool)lockPos.y;
						bool lockPosZ = !(bool)lockPos.z;
						ImGui::Checkbox("X##Pos", &lockPosX);
						ImGui::SameLine();
						ImGui::Checkbox("Y##Pos", &lockPosY);
						ImGui::SameLine();
						ImGui::Checkbox("Z##Pos", &lockPosZ);
						pc->setPositionLock(lockPosX, lockPosY, lockPosZ);

						// Lock Rotation
						ImGui::Text("Lock Rotation");
						reactphysics3d::Vector3 lockRot = pc->getRigidBody()->getAngularLockAxisFactor();
						bool lockRotX = !(bool)lockRot.x;
						bool lockRotY = !(bool)lockRot.y;
						bool lockRotZ = !(bool)lockRot.z;
						ImGui::Checkbox("X##Rot", &lockRotX);
						ImGui::SameLine();
						ImGui::Checkbox("Y##Rot", &lockRotY);
						ImGui::SameLine();
						ImGui::Checkbox("Z##Rot", &lockRotZ);
						pc->setRotationLock(lockRotX, lockRotY, lockRotZ);

						// Delete Button
						if (this->buttonCentered("Delete Rigidbody")) {
							obj->detachComponent(pc);
							obj->setPhysicsOn(false);
						}
					}
				}

				// Separator
				ImGui::NewLine();
				ImGui::Separator();
				ImGui::NewLine();
			}
		}

		ImGui::NewLine();

		if (!hasRigidbody) {
			if (this->buttonCentered("Add Rigidbody")) {
				PhysicsComponent* rb = new PhysicsComponent(obj->getName() + " Rigidbody", obj);
				obj->attachComponent(rb);
				obj->setPhysicsOn(true);
			}
		}
	}
	ImGui::End();
}
