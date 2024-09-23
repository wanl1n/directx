#pragma once
#include "Matrix4x4.h"

__declspec(align(16))
struct Constant {
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};