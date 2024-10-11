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

#include "Circle.h"
#include "BouncingCircle.h"
#include "Quad.h"
#include "PulsingQuad.h"
#include "Area51.h"

#include "Cube.h"
#include "RotatingCube.h"

#include "InputListener.h"

#include "Grid.h"

#include <vector>

class SceneWindow : public Window, public InputListener
{
	public:
		static SceneWindow* getInstance();
		static void initialize();

	private:
		SwapChain* swapChain;

		unsigned long oldTime = 0;

		float oldDelta = 0;
		float newDelta = 0;
		float deltaTime = 0;

		// Scene Tools
		Grid* grid;

	private:
		std::vector<Quad*> QuadList;
		std::vector<Cube*> CubeList;
		std::vector<Circle*> CircleList;

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

		void createQuads();
		void createCubes();

		// Inherited from InputListener.
		void onKeyDown(int key) override;
		void onKeyUp(int key) override;
		void onMouseMove(const Point& deltaMousePos) override;
		void onLeftMouseDown(const Point& mousePos) override;
		void onRightMouseDown(const Point& mousePos) override;
		void onLeftMouseUp(const Point& mousePos) override;
		void onRightMouseUp(const Point& mousePos) override;
};

