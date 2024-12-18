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
#include "CameraManager.h"
#include "UIManager.h"

#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
	public:
		static AppWindow* getInstance();
		static void initialize();

	protected:
		SwapChainPtr swapChain;
		bool isPlaying = false;
		float deltaTime = 0;

	private:
		AppWindow();
		~AppWindow(); 
		AppWindow(AppWindow const&) {};
		AppWindow& operator = (AppWindow const&) {};
		static AppWindow* sharedInstance;

	public:
		void initializeEngine();

		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
		virtual void onFocus() override;
		virtual void onKillFocus() override;

		// Inherited from InputListener.
		void onMouseMove(const Math::Vector2& mousePos) override;
		void onLeftMouseDown(const Math::Vector2& mousePos) override;
		void onRightMouseDown(const Math::Vector2& mousePos) override;
		void onLeftMouseUp(const Math::Vector2& mousePos) override;
		void onRightMouseUp(const Math::Vector2& mousePos) override;

		bool getPlaying();
		void setPlaying(bool playing);
};

