#pragma once
#include <vector>

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

class AppWindow : public Window, public InputListener
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

		// Input testers
		float indexSelected = 0;
		float rotX = 0;
		float rotY = 0;
		float scaler = 1;

	private:
		std::vector<Quad*> GOList;
		std::vector<Quad*> QuadList;
		std::vector<Circle*> CircleList;
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
		virtual void onFocus() override;
		virtual void onKillFocus() override;

		void initializeEngine();

		void createQuad();
		void createCircle();
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

