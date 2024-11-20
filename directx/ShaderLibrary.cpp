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

void ShaderLibrary::requestPixelShaderData(String pixelShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	graphicsEngine->getRenderSystem()->compilePixelShader(pixelShaderName.c_str(), "psmain", shaderByteCode, sizeShader);
}

VertexShaderPtr ShaderLibrary::getVertexShader(String vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL)
		std::cout << "Vertex Shader " << vertexShaderName.c_str() << " not found. Have you initialized it?" << std::endl;
	return this->activeVertexShaders[vertexShaderName];
}

PixelShaderPtr ShaderLibrary::getPixelShader(String pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL)
		std::cout << "Pixel Shader " << pixelShaderName.c_str() << " not found. Have you initialized it?" << std::endl;
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary() 
{
	//initialize and load all shaders for use
	RenderSystem* renderSys = GraphicsEngine::get()->getRenderSystem();

	ShaderNames shaderNames;
	ShaderData shaderData;
	renderSys->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.shaderSize);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = renderSys->createVertexShader(shaderData.shaderByteCode, shaderData.shaderSize);

	renderSys->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.shaderSize);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = renderSys->createPixelShader(shaderData.shaderByteCode, shaderData.shaderSize);

	renderSys->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.shaderSize);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = renderSys->createVertexShader(shaderData.shaderByteCode, shaderData.shaderSize);

	renderSys->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.shaderSize);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = renderSys->createPixelShader(shaderData.shaderByteCode, shaderData.shaderSize);

	renderSys->compilePixelShader(shaderNames.SKYBOX_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.shaderSize);
	this->activePixelShaders[shaderNames.SKYBOX_SHADER_NAME] = renderSys->createPixelShader(shaderData.shaderByteCode, shaderData.shaderSize);

	std::cout << "Shader library initialized. \n";
}

ShaderLibrary::~ShaderLibrary()
{
	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}