#pragma once
#include <iostream>
#include <string>
#include <vector>

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
#include "Math.h"

class Circle : public GameObject
{
protected:
	VertexBuffer* vb;
	ConstantBuffer* cb;
	IndexBuffer* ib;
	BlendState* bs;

	VertexShader* vs;
	PixelShader* ps;

	float center;
	float radius;

public:
	Circle(std::string name, CircleProps props, bool blending);
	~Circle();

	std::vector<Vector3> generateCircleVertices(float radius, int segments);

	virtual void update(float deltaTime, RECT viewport);
	void draw();
	bool release();
};

