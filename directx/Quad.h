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

#include "VertexShader.h"
#include "PixelShader.h"

#include "Vertex.h"
#include "Rect.h"
#include "Vector3.h"

class Quad : GameObject
{
	private:
		VertexBuffer* vb;
		ConstantBuffer* cb;

		QuadVertex initPoints;
		QuadVertex targetPoints;

		/*Vector3 deltaPos;
		Vector3 deltaScale;*/

		float deltaPos = 0;
		float deltaScale = 0;
		float m_angle = 0;

	public:
		Quad(std::string name, void* shader_byte_code, size_t size_shader,
			QuadProps props);

		~Quad();

		void update(float deltaTime, RECT viewport, VertexShader* vs, PixelShader* ps);
		void draw(VertexShader* vs, PixelShader* ps);
		bool release();
};

