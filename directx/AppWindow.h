#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Quad.h"
#include <vector>

class AppWindow : public Window
{
	public:
		static AppWindow* getInstance();
		static void initialize();

	private:
		SwapChain* swapChain;
		VertexShader* vs;
		PixelShader* ps;

		unsigned long oldTime = 0;
		float deltaTime = 0;

	private:
		std::vector<Quad*> GOList;

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
};

