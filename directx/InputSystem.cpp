#include "InputSystem.h"
#include "Windows.h"
#include <iostream>

InputSystem* InputSystem::sharedInstance = nullptr;
InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	if (sharedInstance == NULL)
		return;
	delete sharedInstance;
}

InputSystem::InputSystem() {}
InputSystem::~InputSystem() {}

void InputSystem::update()
{
	// Mouse Movement
	POINT currentMousePos = {};
	::GetCursorPos(&currentMousePos);

	// If first pass, store the current mouse position in the old one.
	if (firstPass) {
		this->oldMousePos = Vector2(currentMousePos.x, currentMousePos.y);
		firstPass = false;
	}

	// If there is a change in position, mouse move.
	if (currentMousePos.x != oldMousePos.x || currentMousePos.y != oldMousePos.y) {
		std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

		while (it != listenersSet.end()) {
			(*it)->onMouseMove(Vector2(currentMousePos.x, currentMousePos.y));
			++it;
		}
	}
	this->oldMousePos = Vector2(currentMousePos.x, currentMousePos.y);
	
	::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);

	// Mouse Keys
	if (::GetKeyboardState(this->keysState)) {
		// Only the bit of the value is evaluated.
		// If this is 1, mouse key is down.
		if (this->keysState[VK_LBUTTON] & 0x80) {
			std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

			while (it != listenersSet.end()) {
				if (this->keysState[VK_LBUTTON] != this->oldKeysState[VK_LBUTTON])
					(*it)->onLeftMouseDown(Vector2(currentMousePos.x, currentMousePos.y));
				++it;
			}
		}
		else {
			if (this->keysState[VK_LBUTTON] != this->oldKeysState[VK_LBUTTON]) {
				std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

				while (it != listenersSet.end()) {
					(*it)->onLeftMouseUp(Vector2(currentMousePos.x, currentMousePos.y));
					++it;
				}
			}
		}

		if (this->keysState[VK_RBUTTON] & 0x80) {
			std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

			while (it != listenersSet.end()) {
				if (this->keysState[VK_RBUTTON] != this->oldKeysState[VK_RBUTTON])
					(*it)->onRightMouseDown(Vector2(currentMousePos.x, currentMousePos.y));
				++it;
			}
		}
		else {
			if (this->keysState[VK_RBUTTON] != this->oldKeysState[VK_RBUTTON]) {
				std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

				while (it != listenersSet.end()) {
					(*it)->onRightMouseUp(Vector2(currentMousePos.x, currentMousePos.y));
					++it;
				}
			}
		}
		// Store current keys state to old keys buffer.
	}
}

void InputSystem::addListener(InputListener* listener)
{
	this->listenersSet.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	this->listenersSet.erase(listener);
}

bool InputSystem::isKeyDown(int key)
{
	bool state = false;

	if (::GetKeyboardState(this->keysState)) {
		if (this->keysState[key] & 0x80)
			state = true;
	}
	return state;
}

bool InputSystem::isKeyUp(int key)
{
	bool state = false;
	if (::GetKeyboardState(this->keysState)) {
		if (this->keysState[key] != this->oldKeysState[key])
			state = true;
	}
	return state;
}

void InputSystem::setCursorPosition(const Vector2& pos)
{
	::SetCursorPos(pos.x, pos.y);
}

void InputSystem::toggleCursor(bool enabled)
{
	::ShowCursor(enabled);
}
