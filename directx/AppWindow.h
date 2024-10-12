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

// Game Objects
#include "GameObjectManager.h"
#include "Quad.h"

#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
	public:
		static AppWindow* getInstance();
		static void initialize();

	private:
		SwapChain* swapChain;

		float deltaTime = 0;

		// Input testers
		float indexSelected = 0;
		float rotX = 0;
		float rotY = 0;
		float scaler = 1;

	private:
		AppWindow();
		~AppWindow(); 
		AppWindow(AppWindow const&) {};
		AppWindow& operator = (AppWindow const&) {};
		static AppWindow* sharedInstance;

		void initializeEngine();
		void createQuads();

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
		virtual void onFocus() override;
		virtual void onKillFocus() override;

		// Inherited from InputListener.
		void onKeyDown(int key) override;
		void onKeyUp(int key) override;
		void onMouseMove(const Point& deltaMousePos) override;
		void onLeftMouseDown(const Point& mousePos) override;
		void onRightMouseDown(const Point& mousePos) override;
		void onLeftMouseUp(const Point& mousePos) override;
		void onRightMouseUp(const Point& mousePos) override;
};

