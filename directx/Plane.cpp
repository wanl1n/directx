#include "Plane.h"
#include "Vertex.h"

Plane::Plane(std::string name, PlaneProps props, bool blending) : GameObject(name)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);

	Vector3 center = props.position;
	Rect rec = { center.x - width / 2, // left
				 center.y + height / 2,// top
				 center.x + width / 2, // right
				 center.y - height / 2 }; // bottom

	PlaneVertex vertices[] = {
		{ Vector3(rec.left,	rec.bottom, 0.0f), props.color },
		{ Vector3(rec.left,	rec.top, 0.0f),	props.color },
		{ Vector3(rec.right, rec.bottom, 0.0f),	props.color },
		{ Vector3(rec.right, rec.top, 0.0f), props.color }
	};

	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);
	this->vb->load(vertices, sizeof(PlaneVertex), size_list, shaderByteCode, sizeShader);

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

	this->height = props.height;
	this->width = props.width;
}

Plane::~Plane()
{}

bool Plane::release()
{
	this->vb->release();
	this->cb->release();
	delete this;
	return true;
}

void Plane::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->project(ORTHOGRAPHIC, viewport);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cc);
}

void Plane::draw()
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

