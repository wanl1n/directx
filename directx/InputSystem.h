#pragma once
#include "InputListener.h"
#include <unordered_set>
#include <vector>
#include "Vector2.h"

class InputSystem
{
	// ATTRIBUTES
	private:
		typedef std::vector<InputListener*> List;
		std::unordered_set<InputListener*> listenersSet;

		// Keyboard
		unsigned char keysState[256] = {};
		unsigned char oldKeysState[256] = {};

		// Mouse
		Math::Vector2 oldMousePos;
		bool firstPass = true;

	// CENTRAL FUNCTIONS
	public:
		static InputSystem* getInstance();
		static void initialize();
		static void destroy();

		void update();
		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);

		bool isKeyDown(int key);
		bool isKeyUp(int key);

	// SINGLETON
	private:
		InputSystem();
		~InputSystem();
		InputSystem(InputSystem const&) {};
		InputSystem& operator = (InputSystem const&) {};
		static InputSystem* sharedInstance;

	// 
	public:
		// Inherited from InputListener.
		void callOnKeyDown(int key);
		void callOnKeyUp(int key);
		void callOnMouseMove(Math::Vector2 mousePos);
		void callOnLeftMouseDown(Math::Vector2 mousePos);
		void callOnRightMouseDown(Math::Vector2 mousePos);
		void callOnLeftMouseUp(Math::Vector2 mousePos);
		void callOnRightMouseUp(Math::Vector2 mousePos);

		void setCursorPosition(const Math::Vector2& pos);
		void toggleCursor(bool enabled);
};

