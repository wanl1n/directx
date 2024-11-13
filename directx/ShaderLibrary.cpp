#include "ShaderLibrary.h"

#include "GraphicsEngine.h"

ShaderLibrary* ShaderLibrary::sharedInstance = nullptr;
ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	graphicsEngine->getRenderSystem()->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
}

VertexShader* ShaderLibrary::getVertexShader(String vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL)
		std::cout << "Vertex Shader " << vertexShaderName.c_str() << " not found. Have you initialized it?" << std::endl;
	return this->activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(String pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL)
		std::cout << "Pixel Shader " << pixelShaderName.c_str() << " not found. Have you initialized it?" << std::endl;
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary() {}
ShaderLibrary::~ShaderLibrary() {}