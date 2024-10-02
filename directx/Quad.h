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
#include "Rect.h"
#include "Vector3.h"

class Quad : public GameObject
{
	protected:
		VertexBuffer* vb;
		ConstantBuffer* cb;
		BlendState* bs;
		
		QuadVertex initPoints;
		QuadVertex targetPoints;

		float height;
		float width;

	public:
		Quad(std::string name, void* shader_byte_code, size_t size_shader,
			QuadProps props, bool blending);

		~Quad();

		virtual void update(float deltaTime, RECT viewport, VertexShader* vs, PixelShader* ps);
		void draw(VertexShader* vs, PixelShader* ps);
		bool release();
};

