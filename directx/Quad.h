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

		VertexShader* vs;
		PixelShader* ps;

		QuadVertex initPoints;
		QuadVertex targetPoints;

		float deltaPos = 0;
		float deltaScale = 0;
		float m_angle = 0;

		// Animations
		float animIntervalCounter = 0;
		bool speedUp = false;
		float speed = 1.57f;

	public:
		Quad(std::string name, QuadProps props);

		~Quad();

		void update(float deltaTime, RECT viewport);
		void draw();
		bool release();
};

