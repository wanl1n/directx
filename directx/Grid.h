#pragma once
#include <iostream>
#include <string>

#include "GameObject.h"

#include "Windows.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "BlendState.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Vertex.h"
#include "Vector3.h"

class Grid
{
private:
	VertexBuffer* vb;
	VertexShader* vs;
	PixelShader* ps;
	BlendState* bs;

	bool showGrid;

public:
	Grid(std::string name, bool showGrid);
	~Grid();

	void draw();
	bool release();
};

