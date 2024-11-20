#pragma once
#include "Vector2.h"

class InputListener {
	public:
		InputListener() {}
		~InputListener() {}

		// Mouse pure virtual callback functions
		virtual void onMouseMove(const Math::Vector2& mousePos) = 0;
		virtual void onLeftMouseDown(const Math::Vector2& mousePos) = 0;
		virtual void onRightMouseDown(const Math::Vector2& mousePos) = 0;
		virtual void onLeftMouseUp(const Math::Vector2& mousePos) = 0;
		virtual void onRightMouseUp(const Math::Vector2& mousePos) = 0;
};