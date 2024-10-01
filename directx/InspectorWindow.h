#pragma once
#include "Windows.h"

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Quad.h"
#include <vector>

class InspectorWindow : public Window
{
public:
	static InspectorWindow* getInstance();
	static void initialize();

private:
	SwapChain* sceneChain;
	SwapChain* inspectorChain;
	VertexShader* vs;
	PixelShader* ps;

	unsigned long oldTime = 0;

	float oldDelta = 0;
	float newDelta = 0;
	float deltaTime = 0;

private:
	std::vector<Quad*> GOList;

private:
	InspectorWindow();
	~InspectorWindow();
	InspectorWindow(InspectorWindow const&) {};
	InspectorWindow& operator = (InspectorWindow const&) {};
	static InspectorWindow* sharedInstance;

public:
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void initializeEngine();
	void initInspector();
	void updateTime();
};

