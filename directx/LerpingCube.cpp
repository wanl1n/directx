#include "LerpingCube.h"
#include "InputSystem.h"

LerpingCube::LerpingCube(std::string name, bool blending) :
	Cube(name, blending, LERPING_CUBE)
{
	this->deltaScale = 0.0f;
	this->deltaTranslate = 0.0f;

	// Test Case 3
	this->upperPosLimit = Vector3(2, 2, 0);
	this->lowerPosLimit = Vector3(-2, -2, 0);
	this->upperScaleLimit = Vector3(1);
	this->lowerScaleLimit = Vector3(0.25f);

	// Test Case 5
	this->transform.scale = Vector3(1);
	this->targetScale = Vector3(3, 0.01f, 3);

	this->speed = 1.0f;

	this->setPosition(transform.position);
}

LerpingCube::~LerpingCube() {}

void LerpingCube::update(float deltaTime, RECT viewport)
{
	this->testCase3(deltaTime);
	//this->testCase5(deltaTime);

	// Update View + Project Matrix
	Cube::update(deltaTime, viewport);
}

void LerpingCube::testCase3(float deltaTime)
{
	this->deltaScale += this->speed * deltaTime;
	this->deltaTranslate += this->speed * 0.5f * deltaTime;

	cc.world.setIdentity();
	cc.world.setScale(Vector3::lerp(upperScaleLimit, lowerScaleLimit, (sin(this->deltaScale) + 1.0f) / 2.0f));

	this->transform.position = Vector3::lerp(upperPosLimit, lowerPosLimit, (sin(deltaTranslate) + 1.0f) / 2.0f);
	this->setPosition(this->transform.position);
}

void LerpingCube::testCase5(float deltaTime)
{
	if (this->transform.scale != targetScale) {
		this->transform.scale = Vector3::lerp(this->transform.scale, targetScale, deltaTime);
		std::cout << name << " Scale : " << transform.scale.x << ", " << transform.scale.y << ", " << transform.scale.z << std::endl;
		cc.world.setScale(this->transform.scale);
	}
}
