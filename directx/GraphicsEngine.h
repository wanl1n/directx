#pragma once
#include <d3d11.h>

#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"

class GraphicsEngine
{
	private:
		RenderSystem* renderSystem = nullptr;
		TextureManager* texManager = nullptr;
		MeshManager* meshManager = nullptr;

		unsigned char meshLayoutByteCode[1024];
		size_t meshLayoutSize = 0;

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
		MeshManager* getMeshManager();
		void getVertexMeshLayoutShaderByteCodeAndSize(void** byteCode, size_t* size);
		static GraphicsEngine* get();
};

