#pragma once

#include <cmath>

//The W component is required to enable perspective, technically making this a 3D vector
struct Vector2D
{
	float u = 0.0f;
	float v = 0.0f;
	float w = 1.0f;
};