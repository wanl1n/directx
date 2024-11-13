#pragma once
#include "PrimitivesInclude.h"
#include "Mesh.h"


class MeshObject : public GameObject
{
	protected:
		MeshPtr mesh;
		TexturePtr texture;

		VertexBufferPtr vb;
		IndexBufferPtr ib;

		VertexShaderPtr vs;
		PixelShaderPtr ps;

	public:
		MeshObject(OBJECT_TYPE type);
		~MeshObject();

		virtual void init();
		virtual void createVertexShader();
		virtual void createPixelShader();
		virtual void createConstantBuffer();

		virtual void update(float deltaTime, RECT viewport) override;
		virtual void draw() override;
};

