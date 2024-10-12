#pragma once
#include "Math.h"

// Constant buffer.
__declspec(align(16))
struct Constant {
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

// Rect
struct Rect {
	float left;
	float top;
	float right;
	float bottom;
};

// Colors
struct QuadColors {
	Vector4 color1;
	Vector4 color2;
	Vector4 color3;
	Vector4 color4;
};

struct DuoColors {
	Vector4 color1;
	Vector4 color2;
};

// Quads
struct QuadVertex {
	Vector3 position;
	Vector3 position1;
	Vector4 color;
	Vector4 color1;
};

struct QuadVertices {
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;
	Vector3 point4;
};

struct QuadProps {
	QuadVertices points1;
	QuadVertices points2;
	QuadColors color1;
	QuadColors color2;
};

// Circles
struct CircleProps {
	Vector3 center;
	float radius;
	float segments;
	Vector4 color;
	Vector4 colorCenter;
};

struct CircleVertex {
	Vector3 point;
	Vector4 color;
};

// Cubes
struct CubeVertex {
	Vector3 position;
	Vector4 color1;
	Vector4 color2;
};

// Planes
struct PlaneProps {
	Vector3 position;
	Vector4 color;
	float width;
	float height;
};

struct PlaneVertex {
	Vector3 position;
	Vector4 color;
};