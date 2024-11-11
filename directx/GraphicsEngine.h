#pragma once
#include <d3d11.h>

#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"

class GraphicsEngine
{
	private:
		RenderSystem* renderSystem = nullptr;
		TextureManager* texManager = nullptr;

	private:
		static GraphicsEngine* sharedInstance;

		GraphicsEngine();
		~GraphicsEngine();
		GraphicsEngine(GraphicsEngine const&) {};
		GraphicsEngine& operator = (GraphicsEngine const&) {};

	public:
		static void initialize();
		static void destroy();

		RenderSystem* getRenderSystem();
		TextureManager* getTextureManager();
		static GraphicsEngine* get();
};

