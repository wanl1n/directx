#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "BlendState.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Quad.h"
#include "PulsingQuad.h"
#include "Area51.h"
#include "Grid.h"
#include <vector>

class SceneWindow : public Window
{
	public:
		static SceneWindow* getInstance();
		static void initialize();

	private:
		SwapChain* swapChain;
		VertexShader* vs;
		PixelShader* ps;

		unsigned long oldTime = 0;

		float oldDelta = 0;
		float newDelta = 0;
		float deltaTime = 0;

		// Scene Tools
		Grid* grid;

	private:
		std::vector<Quad*> GOList;

	private:
		SceneWindow();
		~SceneWindow();
		SceneWindow(SceneWindow const&) {};
		SceneWindow& operator = (SceneWindow const&) {};
		static SceneWindow* sharedInstance;

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		void initializeEngine();
		void updateTime();
};

