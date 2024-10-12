#include "Cube.h"
#include "Constant.h"

Cube::Cube(std::string name, CubeVertex props, bool blending) : GameObject(name)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	this->side = 0.1f;
	// 1. Set up the Vertex buffer.
	CubeVertex vertices[] = { // Cube Vertices
		// FRONT FACE
		{ Vector3(-side, -side, -side), props.color1, props.color1 },
		{ Vector3(-side, side, -side),	props.color1, props.color1 },
		{ Vector3(side, side, -side),	props.color1, props.color1 },
		{ Vector3(side, -side, -side),	props.color1, props.color1 },
		// BACK FACE
		{ Vector3(side, -side, side),	props.color2, props.color2 },
		{ Vector3(side, side, side),	props.color2, props.color2 },
		{ Vector3(-side, side, side),	props.color2, props.color2 },
		{ Vector3(-side, -side, side),	props.color2, props.color2 }
	};
	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);

	// 2. Set up the Index buffer.
	unsigned int indices[] = {
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
	this->ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_indices = ARRAYSIZE(indices);

	// Load into index buffer.
	this->ib->load(indices, size_indices);

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	graphicsEngine->compileVertexShader(L"3DVertexShader.hlsl", "dvsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);
	this->vb->loadIndexed(vertices, sizeof(CubeVertex), size_list, shaderByteCode, sizeShader);

	graphicsEngine->releaseCompiledShader();

	// Creating Pixel Shader
	graphicsEngine->compilePixelShader(L"3DPixelShader.hlsl", "dpsmain", &shaderByteCode, &sizeShader);
	this->ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();

	// 3. Create a constant buffer.
	cc.m_time = 0;
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));

	// 4. Create a blend state.
	this->bs = GraphicsEngine::get()->createBlendState(blending);
}

Cube::~Cube()
{}

bool Cube::release()
{
	this->vb->release();
	this->cb->release();
	this->ib->release();
	this->bs->release();
	delete this;
	return true;
}

void Cube::update(float deltaTime, RECT viewport, Vector3 translate, Vector3 rotate, Vector3 scale)
{
	GameObject::update(deltaTime);

	this->resetView();
	this->project(ORTHOGRAPHIC, viewport);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cc);
}

void Cube::draw()
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
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}

