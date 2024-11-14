#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

class VertexMesh {
public:
	Vector3 pos;
	Vector2 texcoord;
	Vector3 normals;

	VertexMesh() : pos(Vector3(0)), texcoord(Vector2(0)), normals(Vector3(0)) {}
	VertexMesh(Vector3 pos, Vector2 texcoord, Vector3 normals) : pos(pos), texcoord(texcoord), normals(normals) {}
	VertexMesh(const VertexMesh& vmesh) : pos(vmesh.pos), texcoord(vmesh.texcoord), normals(vmesh.normals) {}
	~VertexMesh() {}
};