#include "RotatingCube.h"
#include "EngineTime.h"

RotatingCube::RotatingCube(std::string name, CubeVertex props, bool blending) : Cube(name, props, blending) {}

RotatingCube::~RotatingCube() {}

void RotatingCube::update(float deltaTime, RECT viewport, Vector3 translate, Vector3 rotate, Vector3 scale)
{
	cc.m_world.setScale(scale);

	this->rotateZ(rotate.z);
	this->rotateY(rotate.y);
	this->rotateX(rotate.x);

	Cube::update(deltaTime, viewport);
}
