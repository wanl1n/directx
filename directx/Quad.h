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
#include "Math.h"

class Quad : public GameObject
{
	protected:
		VertexBufferPtr vb;
		ConstantBufferPtr cb;
		BlendStatePtr bs;

		VertexShaderPtr vs;
		PixelShaderPtr ps;
		
		QuadVertex initPoints;
		QuadVertex targetPoints;

		float height;
		float width;

	public:
		Quad(std::string name, QuadProps props, bool blending);

		~Quad();

		virtual void update(float deltaTime, RECT viewport);
		void draw();
		bool release();
};

