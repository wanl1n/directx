#include "Plane.h"
#include "Vertex.h"

Plane::Plane(std::string name, PlaneProps props, bool blending) : GameObject(name)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	
	this->height = props.height;
	this->width = props.width;

	Vector3 center = props.position;
	Rect rec = { center.x - width / 2, // left
				 center.y + height / 2,// top
				 center.x + width / 2, // right
				 center.y - height / 2 }; // bottom
	//std::cout << "Rect: [L]: " << rec.left << " [R]: " << rec.right << " [T]: " << rec.top << " [B]: " << rec.bottom << std::endl;
	PlaneVertex vertices[] = {
		{ Vector3(rec.left,	rec.bottom, 0.0f), props.color },
		{ Vector3(rec.left,	rec.top, 0.0f),	props.color },
		{ Vector3(rec.right, rec.top, 0.0f), props.color },
		{ Vector3(rec.right, rec.bottom, 0.0f),	props.color },

		{ Vector3(rec.right, rec.bottom, 0.0f),	props.color },
		{ Vector3(rec.right, rec.top, 0.0f), props.color },
		{ Vector3(rec.left,	rec.top, 0.0f),	props.color },
		{ Vector3(rec.left,	rec.bottom, 0.0f), props.color }
	};
	this->vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertices);

	// 2. Set up the Index buffer.
	unsigned int indices[] = {
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
	};
	this->ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_indices = ARRAYSIZE(indices);

	// Load into index buffer.
	this->ib->load(indices, size_indices);

	// Shader Attributes
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	// Creating Vertex Shader
	graphicsEngine->compileVertexShader(L"CircleVertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);
	this->vb->loadPlane(vertices, sizeof(PlaneVertex), size_list, shaderByteCode, sizeShader);

	graphicsEngine->releaseCompiledShader();

	// Creating Pixel Shader
	graphicsEngine->compilePixelShader(L"CirclePixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();

	this->transform.rotation.x = 1.57f;
	this->cc.world.setIdentity();
	this->cc.world.setTranslation(this->transform.position);
	this->rotateX(this->transform.rotation.x);

	// Create Constant Buffer and load.
	this->cb = GraphicsEngine::get()->createConstantBuffer();
	this->cb->load(&cc, sizeof(Constant));

	// Blend state.
	this->bs = GraphicsEngine::get()->createBlendState(blending);
}

Plane::~Plane()
{}

bool Plane::release()
{
	this->vb->release();
	this->cb->release();
	this->bs->release();
	this->vs->release();
	this->ps->release();
	delete this;
	return true;
}

void Plane::update(float deltaTime, RECT viewport)
{
	GameObject::update(deltaTime, viewport);

	this->cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cc);
}

void Plane::draw()
{
	DeviceContext* device = GraphicsEngine::get()->getImmediateDeviceContext();

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	device->setVertexShader(vs);
	device->setPixelShader(ps);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->setIndexBuffer(this->ib);
	device->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
	//device->drawTriangleStrip(this->vb->getSizeVertexList(), 0);
}