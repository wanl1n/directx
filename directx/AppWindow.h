#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Quad.h"
#include <vector>

class AppWindow : public Window
{
	private:
		SwapChain* m_swap_chain;

		ConstantBuffer* m_cb;

		VertexShader* m_vs;
		PixelShader* m_ps;

		unsigned long m_old_time = 0;
		float m_delta_time = 0;
		float m_angle = 0;

	private:
		std::vector<Quad*> GOList;

	public:
		AppWindow();
		~AppWindow();

		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
};

