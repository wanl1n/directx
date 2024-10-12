#include "RotatingCube.h"

RotatingCube::RotatingCube(std::string name, CubeVertex props, bool blending) : Cube(name, props, blending) {
	this->randomizeInit();
	this->deltaRot = Vector3(0);
}

RotatingCube::~RotatingCube() {}

void RotatingCube::update(float deltaTime, RECT viewport)
{
	this->deltaRot += deltaTime;

	cc.m_world.setIdentity();

	this->rotateZ(this->deltaRot.z);
	this->rotateY(this->deltaRot.y);
	this->rotateX(this->deltaRot.x);

	Matrix4x4 pos;
	pos.setTranslation(this->transform.position);
	this->cc.m_world *= pos;
	
	Cube::update(deltaTime, viewport);
}

void RotatingCube::randomizeInit()
{
	// Position
	int min = (int)(-100 + this->side * 100);
	int max = (int)(100 - this->side * 100);

	float posX = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;
	float posY = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;

	this->transform.position = Vector3(posX, posY, 1.0f);
	cc.m_world.setScale(Vector3(1));
	cc.m_world.setTranslation(this->transform.position);
	//std::cout << transform.position.x << "," << transform.position.y << std::endl;
}
