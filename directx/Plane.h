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

class Plane : public GameObject
{
	protected:
		VertexBuffer* vb;
		ConstantBuffer* cb;
		BlendState* bs;

		VertexShader* vs;
		PixelShader* ps;

		float height;
		float width;

	public:
		Plane(std::string name, PlaneProps props, bool blending);
		~Plane();

		virtual void update(float deltaTime, RECT viewport) override;
		virtual void draw() override;
		bool release();
};

