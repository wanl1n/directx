#include "Circle.h"
#include "Vertex.h"
#include <iostream>

#include <DirectXMath.h>

Circle::Circle(std::string name, CircleProps props, bool blending) : GameObject(name, CIRCLE)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	renderSystem->compileVertexShader(L"SolidVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = renderSystem->createVertexShader(shaderByteCode, sizeShader);

	std::vector<Vector3> verticesGenerated = this->generateCircleVertices(props.radius, props.segments);
	std::vector<Vertex3D> vertices;
	for (int i = 0; i < verticesGenerated.size(); i++) {
		if (verticesGenerated[i].x == 0 && verticesGenerated[i].y == 0)
			vertices.push_back({ verticesGenerated[i], Vector2(0,0) });
		else
			vertices.push_back( { verticesGenerated[i], Vector2(0,0) } );
	}

	this->vb = renderSystem->createVertexBuffer(vertices, sizeof(Vertex3D), shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();

	// Creating Pixel Shader
	renderSystem->compilePixelShader(L"SolidPixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();

	// Create Constant Buffer and load.
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(Constant));

	// Blend state.
	this->bs = renderSystem->createBlendState(blending);

	this->radius = props.radius;
}

Circle::~Circle() {}

std::vector<Vector3> Circle::generateCircleVertices(float radius, int segments)
{
	std::vector<Vector3> vertices;

	// Center vertex
	vertices.push_back(Vector3(0.0f, 0.0f, 0.0f));

	// Outer circle vertices
	float angleStep = DirectX::XM_2PI / segments;
	for (int i = 0; i < segments; ++i) {
		float angle = i * angleStep;
		float x = radius * cos(angle);
		float y = radius * sin(angle);

		vertices.push_back(Vector3(0.0f, 0.0f, 0.0f));
		vertices.push_back(Vector3(x, y, 0.0f));
	}

	vertices.push_back(Vector3(0.0f, 0.0f, 0.0f));
	vertices.push_back(Vector3(0.1, 0, 0.0f));
	return vertices;
}

void Circle::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &this->cc);
}

void Circle::draw()
{
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->drawTriangleStrip(this->vb->getSizeVertexList(), 0);
}

