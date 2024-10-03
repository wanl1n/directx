#pragma once
#include <iostream>
#include <string>

#include "GameObject.h"

// Engine
#include "Windows.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

// Buffers
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "BlendState.h"

// Shaders
#include "VertexShader.h"
#include "PixelShader.h"

// Structs
#include "Vertex.h"
#include "Rect.h"
#include "Vector3.h"

class Cube : public GameObject
{
protected:
	VertexBuffer* vb;
	ConstantBuffer* cb;
	IndexBuffer* ib;

	VertexShader* vs;
	PixelShader* ps;

	BlendState* bs;

public:
	Cube(std::string name, CubeVertex props, bool blending);

	~Cube();

	virtual void update(float deltaTime, RECT viewport, 
						Vector3 translate = Vector3(0), Vector3 rotate = Vector3(0), Vector3 scale = Vector3(0));
	void draw();
	bool release();
};

