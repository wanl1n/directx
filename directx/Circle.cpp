#include "Circle.h"
#include "Vertex.h"
#include <iostream>

#include <DirectXMath.h>

Circle::Circle(std::string name, CircleProps props, bool blending) : GameObject(name)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	graphicsEngine->compileVertexShader(L"CircleVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);

	std::vector<Vector3> verticesGenerated = this->generateCircleVertices(props.radius, props.segments);
	std::vector<CircleVertex> vertices;
	for (int i = 0; i < verticesGenerated.size(); i++) {
		if (verticesGenerated[i].x == 0 && verticesGenerated[i].y == 0)
			vertices.push_back({ verticesGenerated[i], props.colorCenter });
		else
			vertices.push_back( { verticesGenerated[i], props.color } );
		//std::cout << "circle vertex " << i << ": " << verticesGenerated[i].x << ", " << verticesGenerated[i].y << std::endl;
	}

	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = vertices.size();
	//this->vb->loadC(vertices, sizeof(CircleVertex), size_list, shaderByteCode, sizeShader);
	this->vb->loadCircle(vertices, sizeof(CircleVertex), size_list, shaderByteCode, sizeShader);

	graphicsEngine->releaseCompiledShader();

	// Creating Pixel Shader
	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();

	// Create Constant Buffer and load.
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));

	// Blend state.
	this->bs = GraphicsEngine::get()->createBlendState(blending);

	this->radius = props.radius;
}

Circle::~Circle()
{}

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

bool Circle::release()
{
	this->vb->release();
	this->cb->release();
	delete this;
	return true;
}

void Circle::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->resetView();
	this->project(ORTHOGRAPHIC, viewport);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cc);
}

void Circle::draw()
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);

	// Draw Object.
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(this->vb->getSizeVertexList(), 0);
}

