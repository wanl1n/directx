#pragma once
#include "Circle.h"

class BouncingCircle : public Circle
{
private:
	Vector3 position;
	Vector3 direction;

	float speed = 0.5f;

public:
	BouncingCircle(std::string name, CircleProps props, bool blending);
	~BouncingCircle();

	void update(float deltaTime, RECT viewport);

	void checkBounds(Vector3 offset);

	void randomizeInit();
};

