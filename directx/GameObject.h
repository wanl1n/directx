#pragma once
#include "Windows.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <iostream>

class GameObject
{
	private:
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;

	public:
		GameObject();
		~GameObject();

		bool init(int index, void* shader_byte_code, size_t size_shader);
		bool release();
		
		void draw(VertexShader* vs, PixelShader* ps);
};

