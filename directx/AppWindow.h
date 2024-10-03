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

#include "Cube.h"
#include "RotatingCube.h"

#include <vector>

class AppWindow : public Window
{
	public:
		static AppWindow* getInstance();
		static void initialize();

	private:
		SwapChain* swapChain;

		unsigned long oldTime = 0;

		float oldDelta = 0;
		float newDelta = 0;
		float deltaTime = 0;

	private:
		std::vector<Quad*> GOList;
		std::vector<Quad*> QuadList;
		std::vector<Cube*> CubeList;

	private:
		AppWindow();
		~AppWindow(); 
		AppWindow(AppWindow const&) {};
		AppWindow& operator = (AppWindow const&) {};
		static AppWindow* sharedInstance;

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		void initializeEngine();
		void updateTime();

		void createQuads();
		void createCubes();
};

