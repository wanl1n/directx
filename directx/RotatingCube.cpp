#include "RotatingCube.h"

RotatingCube::RotatingCube(std::string name, CubeVertex props, bool blending) : Cube(name, props, blending) {}

RotatingCube::~RotatingCube() {}

void RotatingCube::update(float deltaTime, RECT viewport)
{
	cc.m_world.setScale(Vector3(1));

	this->rotateZ(0);
	this->rotateY(0);
	this->rotateX(0);

	Cube::update(deltaTime, viewport);
}
