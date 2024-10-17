#include "Quad.h"
#include "Vertex.h"

Quad::Quad(std::string name, QuadProps props, bool blending) : GameObject(name)
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = renderSystem->createVertexShader(shaderByteCode, sizeShader);

	QuadVertex vertices[] = {
		{ props.points1.point1,	props.points2.point1,	props.color1.color1,	props.color2.color1 },
		{ props.points1.point2,	props.points2.point2,	props.color1.color2,	props.color2.color2 },
		{ props.points1.point3,	props.points2.point3,	props.color1.color3,	props.color2.color3 },
		{ props.points1.point4,	props.points2.point4,	props.color1.color4,	props.color2.color4 }
	};

	UINT size_list = ARRAYSIZE(vertices);
	this->vb = renderSystem->createVertexBuffer(vertices, sizeof(QuadVertex), size_list, shaderByteCode, sizeShader);

	renderSystem->releaseCompiledShader();

	// Creating Pixel Shader
	renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();

	// Create Constant Buffer and load.
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(Constant));

	// Blend state.
	this->bs = renderSystem->createBlendState(blending);

	this->height = props.points1.point2.y - props.points1.point1.y;
	this->width = props.points1.point3.x - props.points1.point1.x;
}

Quad::~Quad()
{}

bool Quad::release()
{
	delete vb;
	delete cb;
	delete this;
	return true;
}

void Quad::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &this->cc);
}

void Quad::draw()
{
	DeviceContext* device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

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

