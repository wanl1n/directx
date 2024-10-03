#include "InputSystem.h"
#include "Windows.h"


InputSystem* InputSystem::sharedInstance = nullptr;
InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
	//sharedInstance->init();
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
		this->oldMousePos = Point(currentMousePos.x, currentMousePos.y);
		firstPass = false;
	}

	// If there is a change in position, mouse move.
	if (currentMousePos.x != oldMousePos.x || currentMousePos.y != oldMousePos.y) {
		std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

		while (it != listenersSet.end()) {
			(*it)->onMouseMove(Point(currentMousePos.x - oldMousePos.x, currentMousePos.y - oldMousePos.y));
			++it;
		}
	}
	this->oldMousePos = Point(currentMousePos.x, currentMousePos.y);

	// Keyboard
	if (::GetKeyboardState(this->keysState)) {
		for (unsigned int i = 0; i < 256; i++) {
			// Only the bit of the value is evaluated.
			// If this is 1, key is down.
			if (this->keysState[i] & 0x80) {
				std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

				while (it != listenersSet.end()) {
					// Mouse Key
					if (i == VK_LBUTTON) {
						if (this->keysState[i] != this->oldKeysState[i]) 
							(*it)->onLeftMouseDown(Point(currentMousePos.x, currentMousePos.y));
					}
					if (i == VK_RBUTTON) {
						if (this->keysState[i] != this->oldKeysState[i]) 
							(*it)->onRightMouseDown(Point(currentMousePos.x, currentMousePos.y));
					} 
					else 
						(*it)->onKeyDown(i);
					++it;
				}
			}
			else {
				if (this->keysState[i] != this->oldKeysState[i]) {
					std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

					while (it != listenersSet.end()) {
						// Mouse Key
						if (i == VK_LBUTTON) 
							(*it)->onLeftMouseUp(Point(currentMousePos.x, currentMousePos.y));
						if (i == VK_RBUTTON) 
							(*it)->onRightMouseUp(Point(currentMousePos.x, currentMousePos.y));
						else
							(*it)->onKeyUp(i);
						++it;
					}
				}
			}
		}
		// Store current keys state to old keys buffer.
		::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
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
