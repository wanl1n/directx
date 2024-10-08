#pragma once
#include "Vector3.h"
#include "Vector4.h"

// Quads
struct Vertex {
	Vector3 position;
	Vector3 position1;
	Vector4 color;
	Vector4 color1;
};

struct QuadVertex {
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;
	Vector3 point4;
};

struct QuadColor {
	Vector4 color1;
	Vector4 color2;
	Vector4 color3;
	Vector4 color4;
};

struct QuadProps {
	QuadVertex points1;
	QuadVertex points2;
	QuadColor color1;
	QuadColor color2;
};

struct DuoColor {
	Vector4 color1;
	Vector4 color2;
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