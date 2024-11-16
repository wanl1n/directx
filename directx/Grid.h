#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "GameObject.h"

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

class Grid : public GameObject
{
private:
	VertexBufferPtr vb;
	ConstantBufferPtr cb;
	VertexShaderPtr vs;
	PixelShaderPtr ps;
	BlendStatePtr bs;

	bool showGrid;

public:
	Grid(std::string name, bool showGrid);
	~Grid();

	void update(float deltaTime, RECT viewport);
	void draw();
};

