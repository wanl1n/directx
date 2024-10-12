#include "Area51.h"
#include "EngineTime.h"
#include <cstdlib>

Area51::Area51(std::string name, QuadProps props, bool blending) : Quad(name, props, blending) {
	
	this->position = Vector3(props.points1.point1.x + props.points1.point3.x / 2,
							 props.points1.point1.y + props.points1.point2.y / 2,
							 1.0f);	
	this->width = props.points1.point3.x - props.points1.point1.x;
	this->height = props.points1.point2.y - props.points1.point1.y;

	this->randomizeInit();

	std::cout << "Position: " << position.x << ", " << position.y << std::endl;
	std::cout << "Transform Position: " << transform.position.x << ", " << transform.position.y << std::endl;
	std::cout << "Width, Height: " << width << ", " << height << std::endl;
	std::cout << "Direction: " << direction.x << ", " << direction.y << std::endl;
}

Area51::~Area51() {}

void Area51::update(float deltaTime, RECT viewport)
{
	// Move Up Indefinitely
	cc.world.setScale(Vector3(1));

	/*Matrix4x4 translation;
	Vector3 lerpValue;

	translation.setTranslation(lerpValue = Vector3::lerp(transform.position, transform.position + direction, EngineTime::getDeltaTime() / 50000000));
	this->transform.position += lerpValue;
	this->cc.m_world *= translation;*/

	/*this->translate(this->direction);
	this->checkBounds();*/

	Quad::update(deltaTime, viewport);
}

void Area51::checkBounds()
{
	std::cout << "Position: " << transform.position.x << ", " << transform.position.y << std::endl;
	std::cout << "Direction: " << direction.x << ", " << direction.y << std::endl;

	std::cout << "Left, Right: " << -1.0f + width << ", " << 1.0f - width << std::endl;
	std::cout << "Top, Bottom: " << -1.0f + height << ", " << 1.0f - height << std::endl;
	if (this->transform.position.x < -1.0f + width) {
		std::cout << "Out of bounds left: " << this->transform.position.x << " ! " << -1.0f + width << std::endl;
		this->transform.position.x = -1.0f + width + 0.51f;
		if (this->direction.x < 0)
			this->direction.x = -this->direction.x;
	}
	if (this->transform.position.x > 1.0f - width) {
		std::cout << "Out of bounds right: " << this->transform.position.x << " ! " << 1.0f - width << std::endl;
		this->transform.position.x = 1.0f - width - 0.51f;
		if (this->direction.x > 0)
			this->direction.x = -this->direction.x;
	}

	if (this->transform.position.y < -1.0f + height) {
		std::cout << "Out of bounds top: " << this->transform.position.y << " ! " << -1.0f + height << std::endl;
		this->transform.position.y = -1.0f + height + 0.51f;
		if (this->direction.y < 0)
			this->direction.y = -this->direction.y;
	}
	if (this->transform.position.y > 1.0f - height) {
		std::cout << "Out of bounds top: " << this->transform.position.y << " ! " << 1.0f - height << std::endl;
		this->transform.position.y = 1.0f - height - 0.51f;
		if (this->direction.y > 0)
			this->direction.y = -this->direction.y;
	}
}

void Area51::randomizeInit()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	// Position
	int min = (-1 + width * 2) * 100;
	int max = (1 - width * 2) * 100;

	float posX = (float)(min + (std::rand() % (max - min + 1))) / 100;
	float posY = (float)(min + (std::rand() % (max - min + 1))) / 100;

	this->position = Vector3(posX, posY, 1.0f);
	cc.world.setTranslation(this->position);
	transform.position = this->position;

	// Direction
	min = -100;
	max = 100;

	float dirX = (float)(min + (std::rand() % (max - min + 1))) / 50000.0f;
	float dirY = (float)(min + (std::rand() % (max - min + 1))) / 50000.0f;
	this->direction = Vector3(dirX, dirY, 0);
}
