#pragma once
#include "Vector3D.h"

struct VertexC {
	Vector3D position;
	Vector3D color;
};

struct Vertex {
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

struct QuadVertex {
	Vector3D point1;
	Vector3D point2;
	Vector3D point3;
	Vector3D point4;
};

struct QuadColor {
	Vector3D color1;
	Vector3D color2;
	Vector3D color3;
	Vector3D color4;
};

struct DuoColor {
	Vector3D color1;
	Vector3D color2;
};