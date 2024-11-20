#include "TexturedCube.h"

TexturedCube::TexturedCube(std::string name, bool blending, OBJECT_TYPE type) : Cube("Textured " + name, blending, type)
{
	this->texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
}

TexturedCube::~TexturedCube() {}

void TexturedCube::draw()
{
	GraphicsEngine::get()->getRenderSystem()->setRasterizerState(false);

	ShaderNames shaderNames;
	ShaderLibrary* shaderLib = ShaderLibrary::getInstance();
	DeviceContextPtr device = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	device->setRenderConfig(shaderLib->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME),
							shaderLib->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));
	device->resetTexture();

	// Bind to Shaders.
	device->setConstantBuffer(vs, this->cb);
	device->setConstantBuffer(ps, this->cb);

	// Set Blend State.
	if (this->bs) device->setBlendState(bs);

	// Set Shaders.
	/*device->setVertexShader(vs);
	device->setPixelShader(ps);*/
	device->setTexture(texture);

	// Draw Object.
	device->setVertexBuffer(this->vb);
	device->setIndexBuffer(this->ib);
	device->drawIndexedTriangleList(this->ib->getSizeIndexList(), 0, 0);
}
