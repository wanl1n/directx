#pragma once
#include <iostream>
#include <string>

#include "GameObject.h"

#include "Windows.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "Vertex.h"
#include "Rect.h"

class Quad : GameObject
{
	private:
		VertexBuffer* m_vb;

		Vertex centerVert;
		float width;
		float height;
		Rect bounds;
		Rect target;

	public:
		// Solid Color Quad
		Quad(std::string name, void* shader_byte_code, size_t size_shader, 
			Vertex centerVert, float width, float height);
		// Two-color Gradient (L to R) Quad
		Quad(std::string name, void* shader_byte_code, size_t size_shader,
			Vertex centerVert, float width, float height, Vector3D leftColor, Vector3D rightColor);
		// 4-point Gradient Quad
		Quad(std::string name, void* shader_byte_code, size_t size_shader,
			Vertex centerVert, float width, float height, 
			Vector3D color1, Vector3D color2, Vector3D color3, Vector3D color4);
		~Quad();

		void calculateBounds(bool moving=true);
		void calculateTarget();
		void draw(VertexShader* vs, PixelShader* ps);
		bool release();
};

