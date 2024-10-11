#include "BouncingCircle.h"
#include "EngineTime.h"
#include <cstdlib>

BouncingCircle::BouncingCircle(std::string name, CircleProps props, bool blending) : Circle(name, props, blending) {

	this->randomizeInit();
}

BouncingCircle::~BouncingCircle() {}

void BouncingCircle::update(float deltaTime, RECT viewport)
{
	Vector3 offset = this->direction * this->speed * EngineTime::getDeltaTime();
	transform.position += offset;
	this->checkBounds(offset);

	this->cc.m_world.setTranslation(transform.position);

	Circle::update(deltaTime, viewport);
}

void BouncingCircle::checkBounds(Vector3 offset)
{
	if (this->transform.position.x < -1.26f + radius) {
		this->transform.position -= offset;
		if (this->direction.x < 0)
			this->direction.x = -this->direction.x;
	}
	if (this->transform.position.x > 1.26f - radius) {
		this->transform.position -= offset;
		if (this->direction.x > 0)
			this->direction.x = -this->direction.x;
	}

	if (this->transform.position.y < -1.01f + radius*2) {
		this->transform.position -= offset;
		if (this->direction.y < 0)
			this->direction.y = -this->direction.y;
	}
	if (this->transform.position.y > 1.01f - radius*2) {
		this->transform.position -= offset;
		if (this->direction.y > 0)
			this->direction.y = -this->direction.y;
	}
}

void BouncingCircle::randomizeInit()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	// Position
	int min = -50;
	int max = 50;

	float posX = (float)(min + (std::rand() % (max - min + 1))) / 100;
	float posY = (float)(min + (std::rand() % (max - min + 1))) / 100;

	this->position = Vector3(posX, posY, 1.0f);
	cc.m_world.setScale(Vector3(1));
	cc.m_world.setTranslation(this->position);
	transform.position = this->position;

	// Direction
	min = -100;
	max = 100;

	float dirX = (float)(min + (std::rand() % (max - min + 1))) / 5000.0f;
	float dirY = (float)(min + (std::rand() % (max - min + 1))) / 5000.0f;
	this->direction = Vector3(dirX, dirY, 0);
	this->direction = this->direction.normalize();
}
