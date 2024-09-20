#pragma once
#include <iostream>
#include <string>

#include "Windows.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "Vector3D.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class GameObject
{
	protected:
		std::string m_name;

	public:
		GameObject(std::string name);
		~GameObject();

		virtual bool release() = 0;
};

