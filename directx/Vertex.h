#pragma once
#include "Vector3.h"

struct VertexC {
	Vector3 position;
	Vector3 color;
};

struct Vertex {
	Vector3 position;
	Vector3 position1;
	Vector3 color;
	Vector3 color1;
};

struct QuadVertex {
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;
	Vector3 point4;
};

struct QuadColor {
	Vector3 color1;
	Vector3 color2;
	Vector3 color3;
	Vector3 color4;
};

struct QuadProps {
	QuadVertex points1;
	QuadVertex points2;
	QuadColor color1;
	QuadColor color2;
};

struct DuoColor {
	Vector3 color1;
	Vector3 color2;
};