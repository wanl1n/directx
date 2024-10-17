#include "Grid.h"
#include "Vertex.h"

Grid::Grid(std::string name, bool showGrid) : GameObject("Grid")
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	renderSystem->compileVertexShader(L"GridVertexShader.hlsl", "gvsmain", &shaderByteCode, &sizeShader);
	this->vs = renderSystem->createVertexShader(shaderByteCode, sizeShader);

	// Gridlines
	Vector3 lines[GRIDPOINTS_COUNT];

	float i = -1;
	for (int j = 0; j < GRIDPOINTS_COUNT; j += 4) {
		lines[j] = Vector3(i, 1, 0);
		lines[j + 1] = Vector3(i, -1, 0);
		lines[j + 2] = Vector3(-1, i, 0);
		lines[j + 3] = Vector3(1, i, 0);

		i += GRID_INTERVAL;
	}

	// Load into vertex buffer
	this->vb = renderSystem->createVertexBuffer();
	UINT size_list = ARRAYSIZE(lines);
	this->vb->loadTool(lines, sizeof(Vector3), size_list, shaderByteCode, sizeShader);

	renderSystem->releaseCompiledShader();

	// Creating Pixel Shader
	renderSystem->compilePixelShader(L"GridPixelShader.hlsl", "gpsmain", &shaderByteCode, &sizeShader);
	this->ps = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();

	this->cb = renderSystem->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));

	this->bs = renderSystem->createBlendState(true);

	this->showGrid = showGrid;
}

Grid::~Grid()
{}

bool Grid::release()
{
	this->vb->release();
	this->cb->release();
	this->vs->release();
	this->ps->release();
	this->bs->release();
	delete this;
	return true;
}

void Grid::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->project(ORTHOGRAPHIC, viewport);

	this->cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &this->cc);
}

void Grid::draw()
{
	if (this->showGrid) {
		DeviceContext* device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

		// Set Blend State.
		if (this->bs) device->setBlendState(bs);

		// Set Shaders.
		device->setVertexShader(vs);
		device->setPixelShader(ps);

		// Draw Object.
		device->setVertexBuffer(this->vb);
		device->drawLineList(this->vb->getSizeVertexList(), 0);
	}
}