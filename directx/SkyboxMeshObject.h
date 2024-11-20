#pragma once
#include "MeshObject.h"

class SkyboxMeshObject : public MeshObject
{
	public:
		SkyboxMeshObject();
		~SkyboxMeshObject();

	protected:
		virtual void createPixelShader() override;

		virtual void update(float deltaTime, RECT viewport) override;
		virtual void draw() override;
};

