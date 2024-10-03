#pragma once
#include "InputListener.h"
#include <unordered_set>

class InputSystem
{
	private:
		std::unordered_set<InputListener*> listenersSet;
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

