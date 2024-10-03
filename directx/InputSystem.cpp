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
	if (::GetKeyboardState(this->keysState)) {
		for (unsigned int i = 0; i < 256; i++) {
			// Only the bit of the value is evaluated.
			// If this is 1, key is down.
			if (this->keysState[i] & 0x80) {
				std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

				while (it != listenersSet.end()) {
					(*it)->onKeyDown(i);
					++it;
				}
			}
			else {
				if (this->keysState[i] != this->oldKeysState[i]) {
					std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

					while (it != listenersSet.end()) {
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
