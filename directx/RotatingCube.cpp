#include "RotatingCube.h"

RotatingCube::RotatingCube(std::string name, bool blending) : 
	Cube(name, blending, ROTATING_CUBE) 
{
	this->deltaRot = Vector3(0);
	this->rotDir = Vector3(0);
	this->speed = 1.0f;
	this->randomizeInit();
}

RotatingCube::~RotatingCube() {}

void RotatingCube::update(float deltaTime, RECT viewport)
{
	this->deltaRot += this->rotDir * this->speed * deltaTime;
	this->transform.rotation = Vector3(deltaRot);

	// Update View + Project Matrix
	Cube::update(deltaTime, viewport);
}

void RotatingCube::randomizeInit()
{
	// Position
	int min = (int)(-800 + this->side * 100);
	int max = (int)(800 - this->side * 100);

	float posX = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;
	float posY = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;

	min = (int)(-300 + this->side * 100);
	max = (int)(300 - this->side * 100);

	float posZ = (float)(min + (std::rand() % (max - min + 1))) / 100.0f;

	cc.world.setScale(Vector3(1));
	//this->setPosition(Vector3(posX, posY, posZ));
	this->setPosition(Vector3(0));

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
