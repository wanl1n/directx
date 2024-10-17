#pragma once
#include <d3d11.h>

#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
	private:
		RenderSystem* renderSystem = nullptr;

	private:
		static GraphicsEngine* sharedInstance;

		GraphicsEngine();
		~GraphicsEngine();
		GraphicsEngine(GraphicsEngine const&) {};
		GraphicsEngine& operator = (GraphicsEngine const&) {};

	public:
		static void initialize();
		static void destroy();

		bool init();
		bool release();

		RenderSystem* getRenderSystem();
		static GraphicsEngine* get();
};

