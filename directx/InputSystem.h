#pragma once
#include "InputListener.h"
#include <map>

class InputSystem
{
	private:
		std::map<InputListener*, InputListener*> listenersMap;
		unsigned char keysState[256] = {};
		unsigned char oldKeysState[256] = {};

	public:
		static InputSystem* getInstance();
		static void initialize();

	private:
		InputSystem();
		~InputSystem();
		InputSystem(InputSystem const&) {};
		InputSystem& operator = (InputSystem const&) {};
		static InputSystem* sharedInstance;

	public:
		void update();

		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);
};

