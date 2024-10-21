#pragma once
#include "Cube.h"
#include "Math.h"

class LerpingCube : public Cube
{
private:
	float deltaScale;
	float deltaTranslate;

	Vector3 upperPosLimit;
	Vector3 lowerPosLimit;
	Vector3 upperScaleLimit;
	Vector3 lowerScaleLimit;

	Vector3 targetScale;

	float speed;

public:
	LerpingCube(std::string name, bool blending);
	~LerpingCube();

	void update(float deltaTime, RECT viewport);
	void testCase3(float deltaTime);
	void testCase5(float deltaTime);
};

