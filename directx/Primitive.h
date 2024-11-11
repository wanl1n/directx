#pragma once
#include "PrimitivesInclude.h"

class Primitive : public GameObject
{
	protected:
		VertexBufferPtr vb;
		IndexBufferPtr ib;

		VertexShaderPtr vs;
		PixelShaderPtr ps;

		BlendStatePtr bs;
		TexturePtr texture;

		bool alphaOn;

	public:
		Primitive(std::string name, OBJECT_TYPE type, bool blending);
		~Primitive();

		virtual void init();
		virtual void initializeBuffers() = 0;
		virtual void createVertexShader();
		virtual void createPixelShader();
		virtual void createConstantBuffer();
		virtual void createBlendState(bool blending);

		virtual std::vector<Vertex3D> createVertices() = 0;

		virtual void update(float deltaTime, RECT viewport) override;
		virtual void draw() override;
};

