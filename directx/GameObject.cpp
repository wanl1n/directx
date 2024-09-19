#include "GameObject.h"

struct Vec3 {
	float x, y, z;
};

struct Vertex {
	Vec3 position;
	Vec3 color;
};

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

bool GameObject::init(int index)
{
	Vertex vertices[] = {
		// 1. Rainbow Rectangle
		{ -0.95f, -0.25f, 0.0f,	1, 0, 0 },
		{ -0.95f, 0.25f, 0.0f,	0, 1, 0 },
		{ -0.4f, -0.25f, 0.0f,	0, 0, 1 },
		{ -0.4f, 0.25f, 0.0f,	1, 1, 0 }
	};
	int size = sizeof(vertices) / sizeof(vertices[0]);

	if (index == 1) {
		Vertex vertices1[] = {
			// 1. Rainbow Rectangle
			{ -0.95f, -0.25f, 0.0f,	1, 0, 0 },
			{ -0.95f, 0.25f, 0.0f,	0, 1, 0 },
			{ -0.4f, -0.25f, 0.0f,	0, 0, 1 },
			{ -0.4f, 0.25f, 0.0f,	1, 1, 0 }
		};
		std::copy(vertices, vertices + size, vertices1);
		std::cout << "1";
	}
	else if (index == 2) {
		// 2. Rainbow Triangle
		Vertex vertices2[] = {
			{ -0.3f, -0.25f, 0.0f,	1, 0, 1 },
			{ 0.0f, 0.25f, 0.0f,	0, 1, 0 },
			{ 0.3f, -0.25f, 0.0f,	0, 0, 1 },
			{ -0.4f, 0.25f, 0.0f,	1, 1, 0 }
		};
		std::copy(vertices, vertices + size, vertices2);
		std::cout << "2";
	}
	else {
		// 3. Green Rectangle
		Vertex vertices3[] = {
			{ 0.4f, -0.25f, 0.0f,	0, 1, 0 },
			{ 0.4f, 0.25f, 0.0f,	0, 1, 0 },
			{ 0.95f, -0.25f, 0.0f,	0, 1, 0 },
			{ 0.95f, 0.25f, 0.0f,	0, 1, 0 }
		};
		std::copy(vertices, vertices + size, vertices3);
		std::cout << "3";
	}

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);

	// Shader Attributes
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Creating Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	this->m_vb->load(vertices, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	// Creating Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	return true;
}

bool GameObject::release()
{
	delete this;
	return true;
}

VertexBuffer* GameObject::getVB()
{
	return this->m_vb;
}

VertexShader* GameObject::getVS()
{
	return this->m_vs;
}

PixelShader* GameObject::getPS()
{
	return this->m_ps;
}
