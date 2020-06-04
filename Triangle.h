#pragma once

#include "Vector3D.h"
#include "Vector2D.h"

struct Triangle
{
	Vector3D vertices[3];
	Vector2D textures[3];

	wchar_t symbol;
	short color;

	int ClipAgainstPlane(Vector3D planeP, Vector3D planeN, Triangle &clipped1, Triangle &clipped2)
	{
		planeN.Normalize();

		auto distance = [&](Vector3D &p)
		{
			return (planeN.Dot(p) - planeN.Dot(planeP));
		};

		Vector3D *insidePoints[3]; int insidePointCount = 0;
		Vector3D *outsidePoints[3]; int outsidePointCount = 0;

		Vector2D *insideTextures[3]; int insideTextureCount = 0;
		Vector2D *outsideTextures[3]; int outsideTextureCount = 0;

		float d0 = distance(vertices[0]);
		float d1 = distance(vertices[1]);
		float d2 = distance(vertices[2]);

		if (d0 >= 0.0f) 
		{
			insidePoints[insidePointCount++] = &vertices[0];
			insideTextures[insideTextureCount++] = &textures[0];
		}
		else
		{
			outsidePoints[outsidePointCount++] = &vertices[0];
			outsideTextures[outsideTextureCount++] = &textures[0];
		}
			

		if (d1 >= 0.0f)
		{
			insidePoints[insidePointCount++] = &vertices[1];
			insideTextures[insideTextureCount++] = &textures[1];
		}
		else
		{
			outsidePoints[outsidePointCount++] = &vertices[1];
			outsideTextures[outsideTextureCount++] = &textures[1];
		}
			

		if (d2 >= 0.0f)
		{
			insidePoints[insidePointCount++] = &vertices[2];
			insideTextures[insideTextureCount++] = &textures[2];
		}
		else
		{
			outsidePoints[outsidePointCount++] = &vertices[2];
			outsideTextures[outsideTextureCount++] = &textures[2];
		}

		if (insidePointCount == 0)
		{
			return 0;
		}

		if (insidePointCount == 3)
		{
			clipped1 = *this;
			return 1;
		}

		if (insidePointCount == 1 && outsidePointCount == 2)
		{
			clipped1.symbol = symbol;
			clipped1.color = color;
			//clipped1.color = 0x90;

			clipped1.vertices[0] = *insidePoints[0];
			clipped1.textures[0] = *insideTextures[0];

			float t;

			clipped1.vertices[1].IntersectPlane(planeP, planeN, *insidePoints[0], *outsidePoints[0], t);
			clipped1.textures[1].u = t * (outsideTextures[0]->u - insideTextures[0]->u) + insideTextures[0]->u;
			clipped1.textures[1].v = t * (outsideTextures[0]->v - insideTextures[0]->v) + insideTextures[0]->v;
			clipped1.textures[1].w = t * (outsideTextures[0]->w - insideTextures[0]->w) + insideTextures[0]->w;

			clipped1.vertices[2].IntersectPlane(planeP, planeN, *insidePoints[0], *outsidePoints[1], t);
			clipped1.textures[2].u = t * (outsideTextures[1]->u - insideTextures[0]->u) + insideTextures[0]->u;
			clipped1.textures[2].v = t * (outsideTextures[1]->v - insideTextures[0]->v) + insideTextures[0]->v;
			clipped1.textures[2].w = t * (outsideTextures[1]->w - insideTextures[0]->w) + insideTextures[0]->w;

			return 1;
		}

		if (insidePointCount == 2 && outsidePointCount == 1)
		{
			clipped1.symbol = symbol;
			clipped1.color = color;
			//clipped1.color = 0xC0;

			clipped2.symbol = symbol;
			clipped2.color = color;
			//clipped2.color = 0xA0;

			float t;

			clipped1.vertices[0] = *insidePoints[0];
			clipped1.textures[0] = *insideTextures[0];

			clipped1.vertices[1] = *insidePoints[1];
			clipped1.textures[1] = *insideTextures[1];

			clipped1.vertices[2].IntersectPlane(planeP, planeN, *insidePoints[0], *outsidePoints[0], t);
			clipped1.textures[2].u = t * (outsideTextures[0]->u - insideTextures[0]->u) + insideTextures[0]->u;
			clipped1.textures[2].v = t * (outsideTextures[0]->v - insideTextures[0]->v) + insideTextures[0]->v;
			clipped1.textures[2].w = t * (outsideTextures[0]->w - insideTextures[0]->w) + insideTextures[0]->w;

			clipped2.vertices[0] = *insidePoints[1];
			clipped2.textures[0] = *insideTextures[1];

			clipped2.vertices[1] = clipped1.vertices[2];
			clipped2.textures[1] = clipped1.textures[2];

			clipped2.vertices[2].IntersectPlane(planeP, planeN, *insidePoints[1], *outsidePoints[0], t);
			clipped2.textures[2].u = t * (outsideTextures[0]->u - insideTextures[1]->u) + insideTextures[1]->u;
			clipped2.textures[2].v = t * (outsideTextures[0]->v - insideTextures[1]->v) + insideTextures[1]->v;
			clipped2.textures[2].w = t * (outsideTextures[0]->w - insideTextures[1]->w) + insideTextures[1]->w;

			return 2;
		}
	}
};
