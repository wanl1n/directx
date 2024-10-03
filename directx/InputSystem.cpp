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
		for (int i = 0; i < 256; i++) {
			// Only the bit of the value is evaluated.
			// If this is 1, key is down.
			if (this->keysState[i] & 0x80) {
				std::map<InputListener*, InputListener*>::iterator it = listenersMap.begin();

				while (it != listenersMap.end()) {
					it->second->onKeyDown(i);
					++it;
				}
			}
			else {
				if (this->keysState[i] != this->oldKeysState[i]) {
					std::map<InputListener*, InputListener*>::iterator it = listenersMap.begin();

					while (it != listenersMap.end()) {
						it->second->onKeyUp(i);
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
	this->listenersMap.insert(std::make_pair <InputListener*, InputListener*>
		(std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));
}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = listenersMap.find(listener);

	if (it != listenersMap.end())
		listenersMap.erase(it);
}
