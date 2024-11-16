#pragma once
#include "Vector3.h"

namespace Struct {
	struct Quaternion {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;
	};

	struct Transform {
		Math::Vector3 position;
		Math::Vector3 scale;
		Math::Vector3 rotation;
		Quaternion orientation;
	};
}