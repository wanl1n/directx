#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
	private:
		std::unordered_set<InputListener*> listenersSet;

		// Keyboard
		unsigned char keysState[256] = {};
		unsigned char oldKeysState[256] = {};

		// Mouse
		Point oldMousePos;
		bool firstPass = true;

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

		bool isKeyDown(int key);
		bool isKeyUp(int key);

		void setCursorPosition(const Point& pos);
		void toggleCursor(bool enabled);
};

