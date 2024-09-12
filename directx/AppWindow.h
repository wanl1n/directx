#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

class AppWindow : public Window
{
	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexShader* m_vs;

	public:
		AppWindow();
		~AppWindow();

		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
};

