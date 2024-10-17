#include "Grid.h"
#include "Vertex.h"

Grid::Grid(std::string name, bool showGrid) : GameObject("Grid")
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	// Gridlines
	std::vector<Vertex3D> lines;

	float i = -1;
	for (int j = 0; j < GRIDPOINTS_COUNT; j += 4) {
		lines.push_back({ Vector3(i, 1, 0), GRAY });
		lines.push_back({ Vector3(i, -1, 0), GRAY });
		lines.push_back({ Vector3(-1, i, 0), GRAY });
		lines.push_back({ Vector3(1, i, 0), GRAY });

		i += GRID_INTERVAL;
	}
	
	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	renderSystem->compileVertexShader(L"SolidVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = renderSystem->createVertexShader(shaderByteCode, sizeShader);
	this->vb = renderSystem->createVertexBuffer(lines, sizeof(Vertex3D), shaderByteCode, sizeShader);

	renderSystem->releaseCompiledShader();

	// Creating Pixel Shader
	renderSystem->compilePixelShader(L"SolidPixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();

	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(Constant));

	this->bs = renderSystem->createBlendState(true);

	this->showGrid = showGrid;
}

Grid::~Grid()
{
	delete vb;
	delete cb;
	delete vs;
	delete ps;
	delete bs;
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