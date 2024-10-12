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

#include "GameObjectManager.h"
#include "Grid.h"

#include "InputListener.h"


class SceneWindow : public Window, public InputListener
{
	public:
		static SceneWindow* getInstance();
		static void initialize();

	private:
		SwapChain* swapChain;

		float deltaTime = 0;

		// Scene Tools
		Grid* grid;

	private:
		SceneWindow();
		~SceneWindow();
		SceneWindow(SceneWindow const&) {};
		SceneWindow& operator = (SceneWindow const&) {};
		static SceneWindow* sharedInstance;

	public:
		void initializeEngine();

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

