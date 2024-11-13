#pragma once
#include "Vector2.h"

class InputListener {
	public:
		InputListener() {}
		~InputListener() {}

		// Mouse pure virtual callback functions
		virtual void onMouseMove(const Vector2& mousePos) = 0;
		virtual void onLeftMouseDown(const Vector2& mousePos) = 0;
		virtual void onRightMouseDown(const Vector2& mousePos) = 0;
		virtual void onLeftMouseUp(const Vector2& mousePos) = 0;
		virtual void onRightMouseUp(const Vector2& mousePos) = 0;
};