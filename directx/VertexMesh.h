#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

class VertexMesh {
public:
	Vector3 pos;
	Vector2 texcoord;

	VertexMesh() : pos(Vector3(0)), texcoord(Vector2(0)) {}
	VertexMesh(Vector3 pos, Vector2 texcoord) : pos(pos), texcoord(texcoord) {}
	VertexMesh(const VertexMesh& vmesh) : pos(vmesh.pos), texcoord(vmesh.texcoord) {}
	~VertexMesh() {}
};