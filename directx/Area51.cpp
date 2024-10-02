#include "Area51.h"

Area51::Area51(std::string name, void* shader_byte_code, size_t size_shader,
	QuadProps props, bool blending) : Quad(name, shader_byte_code, size_shader, props, blending) {}

Area51::~Area51() {}

void Area51::update(float deltaTime, RECT viewport, VertexShader* vs, PixelShader* ps)
{
	// Move Right Indefinitely
	//transform.position.x += 1.0f * deltaTime;
	/*if (transform.position.x > 1 + width / 2)
		transform.position.x = 0;
	cc.m_world.setTranslation(transform.position);*/

	// Test Cases
	this->translate(Vector3(0, 0.0000001f, 0));
	/*this->scale(Vector3(0.5f, 0, 0));*/
	std::cout << this->m_name << std::endl;
	cc.m_world.printMatrix();

	Quad::update(deltaTime, viewport, vs, ps);
}
