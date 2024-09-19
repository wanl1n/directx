#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "GameObject.h"
#include <list>

class AppWindow : public Window
{
	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;

	private:
		GameObject m_quad;
		std::list<GameObject> GOList;

	public:
		AppWindow();
		~AppWindow();

		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
};

