#include "Grid.h"
#include "Constant.h"

Grid::Grid(std::string name, bool showGrid)
{
	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"GridVertexShader.hlsl", "gvsmain", &shaderByteCode, &sizeShader);
	this->vs = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

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
	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(lines);
	this->vb->load(lines, sizeof(Vector3), size_list, shaderByteCode, sizeShader, "Grid");

	GraphicsEngine::get()->releaseCompiledShader();

	// Creating Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"GridPixelShader.hlsl", "gpsmain", &shaderByteCode, &sizeShader);
	this->ps = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();

	this->bs = GraphicsEngine::get()->createBlendState(true);

	this->showGrid = showGrid;
}

Grid::~Grid()
{}

bool Grid::release()
{
	this->vb->release();
	this->vs->release();
	this->ps->release();
	this->bs->release();
	delete this;
	return true;
}

void Grid::draw()
{
	if (this->showGrid) {
		DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

		// Set Blend State.
		if (this->bs) device->setBlendState(bs);

		// Set Shaders.
		device->setVertexShader(vs);
		device->setPixelShader(ps);

		// Draw Object.
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vb);
		GraphicsEngine::get()->getImmediateDeviceContext()->drawLineList(this->vb->getSizeVertexList(), 0);
	}
}