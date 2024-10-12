#pragma once
#include "Point.h"

class InputListener {
	public:
		InputListener() {}
		~InputListener() {}

		// Keyboard pure virtual callback functions
		virtual void onKeyDown(int key) = 0;
		virtual void onKeyUp(int key) = 0;

		// Mouse pure virtual callback functions
		virtual void onMouseMove(const Point& mousePos) = 0;
		virtual void onLeftMouseDown(const Point& mousePos) = 0;
		virtual void onRightMouseDown(const Point& mousePos) = 0;
		virtual void onLeftMouseUp(const Point& mousePos) = 0;
		virtual void onRightMouseUp(const Point& mousePos) = 0;
};