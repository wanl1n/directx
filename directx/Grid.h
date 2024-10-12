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

class Grid : public GameObject
{
private:
	VertexBuffer* vb;
	ConstantBuffer* cb;
	VertexShader* vs;
	PixelShader* ps;
	BlendState* bs;

	bool showGrid;

public:
	Grid(std::string name, bool showGrid);
	~Grid();

	void update(float deltaTime, RECT viewport);
	void draw();
	bool release();
};

