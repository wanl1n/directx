#pragma once
#include "Math.h"

// Constant buffer.
__declspec(align(16))
struct Constant {
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 proj;
	Vector4 lightDir;
	Vector4 cameraPos;
};

// Rect
struct Rect {
	float left;
	float top;
	float right;
	float bottom;
};

struct Bounds {
	float minX, maxX, minY, maxY, minZ, maxZ;
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
	Math::Vector3 position;
	Math::Vector3 position1;
	Vector4 color;
	Vector4 color1;
};

struct QuadVertices {
	Math::Vector3 point1;
	Math::Vector3 point2;
	Math::Vector3 point3;
	Math::Vector3 point4;
};

struct QuadProps {
	QuadVertices points1;
	QuadVertices points2;
	QuadColors color1;
	QuadColors color2;
};

// Circles
struct CircleProps {
	Math::Vector3 center;
	float radius;
	float segments;
	Vector4 color;
	Vector4 colorCenter;
};

// Cubes
struct CubeProps {
	Math::Vector3 position;
	float side;
	Vector4 color1;
	Vector4 color2;
};

// Planes
struct PlaneProps {
	Math::Vector3 position;
	Vector4 color;
	float width;
	float height;
};

struct Vertex3D {
	Math::Vector3 position;
	Math::Vector2 texcoord;
	Vector4 color;
};

struct BaseVertex {
	Math::Vector3 position;
	Math::Vector2 texcoord;
};