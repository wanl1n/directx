#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

using namespace Math;

class VertexMesh {
public:
	Math::Vector3 pos;
	Math::Vector2 texcoord;
	Math::Vector3 normals;

	VertexMesh() : pos(Math::Vector3(0)), texcoord(Math::Vector2(0)), normals(Math::Vector3(0)) {}
	VertexMesh(Math::Vector3 pos, Math::Vector2 texcoord, Math::Vector3 normals) : pos(pos), texcoord(texcoord), normals(normals) {}
	VertexMesh(const VertexMesh& vmesh) : pos(vmesh.pos), texcoord(vmesh.texcoord), normals(vmesh.normals) {}
	~VertexMesh() {}
};