#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb_rr;
		VertexBuffer* m_vb_rt;
		VertexBuffer* m_vb_gr;
		VertexShader* m_vs;
		PixelShader* m_ps;

	public:
		AppWindow();
		~AppWindow();

		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
};

