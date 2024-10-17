#pragma once
#include "PrimitivesInclude.h"

class Primitive : public GameObject
{
protected:
	VertexBuffer* vb;
	ConstantBuffer* cb;
	IndexBuffer* ib;

	VertexShader* vs;
	PixelShader* ps;

	BlendState* bs;

public:
	Primitive(std::string name, bool blending);
	~Primitive();

	virtual void update(float deltaTime, RECT viewport) override;
	virtual void draw() override;
	virtual bool release();
};

