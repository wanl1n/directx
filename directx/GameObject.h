#pragma once
#include "Windows.h"
#include "GraphicsEngine.h"
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

		bool init(int index = 1);
		bool release();

		VertexBuffer* getVB();
		VertexShader* getVS();
		PixelShader* getPS();
};

