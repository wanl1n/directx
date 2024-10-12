#pragma once
#include "Vector4.h"

const Vector4 CREAM = Vector4(1.0f, 0.99f, 0.81f, 1.0f);
const Vector4 MATCHA = Vector4(139.0f / 255.0f, 168.0f / 255.0f, 136.0f / 255.0f, 1.0f);
const Vector4 SPACE = Vector4(59.0f/255.0f, 59.0f/255.0f, 88.0f/255.0f, 1.0f);
const Vector4 LAVENDER = Vector4(215 / 255.0f, 180 / 255.0f, 243 / 255.0f, 1.0f);
const Vector4 PINK = Vector4(0.957f, 0.761f, 0.761f, 1.0f);

const Vector4 GRAY = Vector4(0.5f, 0.5f, 0.5f, 0.1f);
const Vector4 WHITE = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 BLACK = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
const Vector4 CLEAR = Vector4(1, 1, 1, 0.0f);

const int ORTHOGRAPHIC = 0;
const float GRID_INTERVAL = 0.1f;
const int GRIDPOINTS_COUNT = (int)(((2 / 0.1f)) * 4);

static const int NUM_SAMPLES = 10;

enum PRIMITIVE {
	QUAD = 0,
	PULSING_QUAD,
	AREA51_QUAD,
	CIRCLE,
	BOUNCING_CIRCLE,
	CUBE,
	ROTATING_CUBE,
	PLANE
};