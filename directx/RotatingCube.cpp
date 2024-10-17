#include "RotatingCube.h"

RotatingCube::RotatingCube(std::string name, bool blending) : Cube(name, blending, ROTATING_CUBE) {
	this->deltaRot = Vector3(0);
	this->rotDir = Vector3(0);
	this->speed = 0;
	this->randomizeInit();
}

RotatingCube::~RotatingCube() {}

void RotatingCube::update(float deltaTime, RECT viewport)
{
	this->deltaRot += this->rotDir * this->speed * deltaTime;

	// Reset world space matrix.
	cc.world.setIdentity();

	// Rotate cube.
	this->rotateZ(this->deltaRot.z);
	this->rotateY(this->deltaRot.y);
	this->rotateX(this->deltaRot.x);

	// Move back to actual position.
	Matrix4x4 pos;
	pos.setTranslation(this->transform.position);
	this->cc.world *= pos;
	
	// Project
	Cube::update(deltaTime, viewport);
}

void RotatingCube::randomizeInit()
{
	// Position
	int min = (int)(-100 + this->side * 100);
	int max = (int)(100 - this->side * 100);

	float posX = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;
	float posY = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;
	
	min = (int)(-300 + this->side * 100);
	max = (int)(300 - this->side * 100);
	
	float posZ = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;

	this->transform.position = Vector3(posX, posY, posZ);
	cc.world.setScale(Vector3(1));
	cc.world.setTranslation(this->transform.position);
	//std::cout << transform.position.x << "," << transform.position.y << std::endl;
	
	// Rotation Direction
	min = -100;
	max = 100;

	float dirX = (float)(min + (std::rand() % (max - min + 1))) / 5000.0f;
	float dirY = (float)(min + (std::rand() % (max - min + 1))) / 5000.0f;
	this->rotDir = Vector3(dirX, dirY, 0);
	this->rotDir = this->rotDir.normalize();

	min = 1;
	max = 5;
	this->speed = (float)(min + (std::rand() % (max - min + 1)));
}
