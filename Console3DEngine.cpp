#include "ConsoleGameEngine.h"

#include <algorithm>

#include "Mesh.h"
#include "Matrix4D.h"

class ConsoleEngine3D : public ConsoleGameEngine
{
private:
	Mesh model;
	Sprite *sprTexture;

	Matrix4D matProj;

	Vector3D camera;
	Vector3D lookDir;

	float yaw;
	float theta;

	float *depthBuffer = nullptr;

	CHAR_INFO GetColor(float luminance)
	{
		short bgColor, fgColor;
		wchar_t symbol;
		int pixelBw = (int)(13.0f * luminance);
		switch (pixelBw)
		{
			case 0: bgColor = BG_BLACK; fgColor = FG_BLACK; symbol = PIXEL_SOLID; break;

			case 1: bgColor = BG_BLACK; fgColor = FG_DARK_GRAY; symbol = PIXEL_QUARTER; break;
			case 2: bgColor = BG_BLACK; fgColor = FG_DARK_GRAY; symbol = PIXEL_HALF; break;
			case 3: bgColor = BG_BLACK; fgColor = FG_DARK_GRAY; symbol = PIXEL_THREEQUARTERS; break;
			case 4: bgColor = BG_BLACK; fgColor = FG_DARK_GRAY; symbol = PIXEL_SOLID; break;

			case 5: bgColor = BG_DARK_GRAY; fgColor = FG_GRAY; symbol = PIXEL_QUARTER; break;
			case 6: bgColor = BG_DARK_GRAY; fgColor = FG_GRAY; symbol = PIXEL_HALF; break;
			case 7: bgColor = BG_DARK_GRAY; fgColor = FG_GRAY; symbol = PIXEL_THREEQUARTERS; break;
			case 8: bgColor = BG_DARK_GRAY; fgColor = FG_GRAY; symbol = PIXEL_SOLID; break;

			case 9:  bgColor = BG_GRAY; fgColor = FG_WHITE; symbol = PIXEL_QUARTER; break;
			case 10: bgColor = BG_GRAY; fgColor = FG_WHITE; symbol = PIXEL_HALF; break;
			case 11: bgColor = BG_GRAY; fgColor = FG_WHITE; symbol = PIXEL_THREEQUARTERS; break;
			case 12: bgColor = BG_GRAY; fgColor = FG_WHITE; symbol = PIXEL_SOLID; break;

			default: bgColor = BG_BLACK; fgColor = FG_BLACK; symbol = PIXEL_SOLID; break;
		}

		CHAR_INFO result;
		result.Char.UnicodeChar = symbol;
		result.Attributes = bgColor | fgColor;
		return result;
	}

public:
	bool OnStart() override
	{
		SetApplicationTitle(L"3D Engine");

		depthBuffer = new float[GetScreenWidth() * GetScreenHeight()];

		model.triangles = {

			//SOUTH
			{ 0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f },

			//EAST           																			   
			{ 1.0f, 0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f },

			//NORTH           																			   
			{ 1.0f, 0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f },

			//WEST            																			   
			{ 0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f },

			//TOP             																			   
			{ 0.0f, 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f },

			//BOTTOM          																			  
			{ 1.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f },

		};

		//model.LoadFromObjectFile("mountains.obj");
		sprTexture = new Sprite(L"brick_wall.spr");

		//Projection matrix
		matProj.Projection(90.0f, (float)GetScreenHeight() / (float)GetScreenWidth(), 0.1f, 1000.0f);

		return true;
	}

	bool OnUpdate(float elapsedTime) override
	{
		//Handle user movement
		if (GetKey(VK_UP).held)
			camera.y += 8.0f * elapsedTime;

		if (GetKey(VK_DOWN).held)
			camera.y -= 8.0f * elapsedTime;

		Vector3D forward = lookDir * 8.0f * elapsedTime;

		if (GetKey('W').held)
			camera += forward;

		if (GetKey('S').held)
			camera -= forward;

		if (GetKey('A').held)
			yaw -= 2.0f * elapsedTime;

		if (GetKey('D').held)
			yaw += 2.0f * elapsedTime;

		//Translate our world slightly away from the camera
		Matrix4D matTranslation;
		matTranslation.Translation(0.0f, 0.0f, 5.0f);

		Matrix4D matRotX, matRotZ;
		matRotX.RotationX(theta);
		matRotZ.RotationZ(theta * 0.5f);

		//theta += elapsedTime;

		//Create the world matrix
		Matrix4D matWorld;
		matWorld.Indentity();
		matWorld = matRotX * matRotZ;
		matWorld *= matTranslation;

		//Create "Point At" Matrix for camera
		Vector3D up = { 0.0f, 1.0f, 0.0f };
		Vector3D target = { 0.0f, 0.0f, 1.0f };

		//Create matrix that rotates camera around the Y axis according to user's input
		Matrix4D matCameraRot;
		matCameraRot.RotationY(yaw);

		//Determine the new camera direction and new relative target position
		lookDir = matCameraRot * target;	//Update direction we're looking at by rotating
		target = camera + lookDir;			//Offset target by camera's possition

		//Create the camera matrix that points from the camera position towards camera target
		Matrix4D matCamera;
		matCamera.PointAt(camera, target, up);

		//Create view matrix that brings objects from camera space to screen space (essentially an inverse of what camera is doing)
		Matrix4D matView;
		matView.QuickInverse(matCamera);

		std::vector<Triangle> trisToDraw;

		//Project the model
		for (auto triangle : model.triangles)
		{
			Triangle triProjected, triTransformed, triViewed;

			//Transform the triangle into world space
			triTransformed.vertices[0] = matWorld * triangle.vertices[0];
			triTransformed.vertices[1] = matWorld * triangle.vertices[1];
			triTransformed.vertices[2] = matWorld * triangle.vertices[2];

			//Carry on the texture information
			triTransformed.textures[0] = triangle.textures[0];
			triTransformed.textures[1] = triangle.textures[1];
			triTransformed.textures[2] = triangle.textures[2];

			//Find the normal to the triangle
			Vector3D normal, line1, line2;

			//We can take 2 arbitrary lines out of 3 that make up the triangle
			line1 = triTransformed.vertices[1] - triTransformed.vertices[0];
			line2 = triTransformed.vertices[2] - triTransformed.vertices[0];

			//Cross product gives us the normal, which then must be normalized
			normal = line1.Cross(line2);
			normal.Normalize();

			//Cast a ray from camera to triangle
			Vector3D cameraRay = triTransformed.vertices[0] - camera;

			//Check if triangle is visible to perform culling
			if (normal.Dot(cameraRay) < 0.0f)
			{
				//Illumination
				Vector3D directionalLight = { 0.0f, 1.0f, -1.0f };
				directionalLight.Normalize();

				//Determine how much of the light reaches the triangle's surface
				float dot = max(0.1f, directionalLight.Dot(normal));

				//Choose shading and color
				CHAR_INFO c = GetColor(dot);
				triTransformed.symbol = c.Char.UnicodeChar;
				triTransformed.color = c.Attributes;

				//Since we've determined that the triangle is visible by our camera, we can bring it from world space to view space
				triViewed.vertices[0] = matView * triTransformed.vertices[0];
				triViewed.vertices[1] = matView * triTransformed.vertices[1];
				triViewed.vertices[2] = matView * triTransformed.vertices[2];

				//Carry on the shading information
				triViewed.symbol = triTransformed.symbol;
				triViewed.color = triTransformed.color;

				//Carry on the texture information
				triViewed.textures[0] = triTransformed.textures[0];
				triViewed.textures[1] = triTransformed.textures[1];
				triViewed.textures[2] = triTransformed.textures[2];

				//Clip the triangle relative to our near Z plane
				int clippedTriangles = 0;
				Triangle clipped[2];

				clippedTriangles = triViewed.ClipAgainstPlane(
					{ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, clipped[0], clipped[1]
				);

				//Process each triangle that we've got from clipping (if any)
				for (int n = 0; n < clippedTriangles; n++)
				{
					//Project the triangle into 2D screen space
					triProjected.vertices[0] = matProj * clipped[n].vertices[0];
					triProjected.vertices[1] = matProj * clipped[n].vertices[1];
					triProjected.vertices[2] = matProj * clipped[n].vertices[2];

					//Carry on the shading information
					triProjected.symbol = clipped[n].symbol;
					triProjected.color = clipped[n].color;

					//Carry on the texture information
					triProjected.textures[0] = clipped[n].textures[0];
					triProjected.textures[1] = clipped[n].textures[1];
					triProjected.textures[2] = clipped[n].textures[2];

					triProjected.textures[0].u /= triProjected.vertices[0].w;
					triProjected.textures[1].u /= triProjected.vertices[1].w;
					triProjected.textures[2].u /= triProjected.vertices[2].w;

					triProjected.textures[0].v /= triProjected.vertices[0].w;
					triProjected.textures[1].v /= triProjected.vertices[1].w;
					triProjected.textures[2].v /= triProjected.vertices[2].w;

					triProjected.textures[0].w = 1.0f / triProjected.vertices[0].w;
					triProjected.textures[1].w = 1.0f / triProjected.vertices[1].w;
					triProjected.textures[2].w = 1.0f / triProjected.vertices[2].w;

					//Divide each vertex by Z component (stored in W) to achieve perspective
					triProjected.vertices[0] /= triProjected.vertices[0].w;
					triProjected.vertices[1] /= triProjected.vertices[1].w;
					triProjected.vertices[2] /= triProjected.vertices[2].w;

					//X and Y are inverted, so invert back
					triProjected.vertices[0].x *= -1.0f;
					triProjected.vertices[0].y *= -1.0f;
					triProjected.vertices[1].x *= -1.0f;
					triProjected.vertices[1].y *= -1.0f;
					triProjected.vertices[2].x *= -1.0f;
					triProjected.vertices[2].y *= -1.0f;

					//Offest vertices into visible normalized space
					Vector3D offset = { 1.0f, 1.0f, 0.0f };

					triProjected.vertices[0] += offset;
					triProjected.vertices[1] += offset;
					triProjected.vertices[2] += offset;

					//Scale the triangle
					triProjected.vertices[0].x *= 0.5f * (float)GetScreenWidth();
					triProjected.vertices[0].y *= 0.5f * (float)GetScreenHeight();
					triProjected.vertices[1].x *= 0.5f * (float)GetScreenWidth();
					triProjected.vertices[1].y *= 0.5f * (float)GetScreenHeight();
					triProjected.vertices[2].x *= 0.5f * (float)GetScreenWidth();
					triProjected.vertices[2].y *= 0.5f * (float)GetScreenHeight();

					//Store triangles for sorting
					trisToDraw.push_back(triProjected);
				}
			}
		}

		//Sort triangles from back to front
		/*sort(trisToDraw.begin(), trisToDraw.end(), [](Triangle &t1, Triangle &t2) 
		{
			float threeInv = 1.0f / 3.0f;
			float z1 = (t1.vertices[0].z + t1.vertices[1].z + t1.vertices[2].z) * threeInv;
			float z2 = (t2.vertices[0].z + t2.vertices[1].z + t2.vertices[2].z) * threeInv;
			return z1 > z2;
		});*/

		//ClearScreen();
		Fill(0, 0, GetScreenWidth() * GetScreenHeight(), ' ', BG_CYAN);

		for (int i = 0; i < GetScreenWidth() * GetScreenHeight(); i++)
			depthBuffer[i] = 0.0f;

		//Clip each triangle against edges of the screen
		for (auto &triangle : trisToDraw)
		{
			Triangle clipped[2];
			std::list<Triangle> triangles;
			triangles.push_back(triangle);
			int newTriangles = 1;

			for (int p = 0; p < 4; p++)
			{
				int trisToAdd = 0;
				while (newTriangles > 0)
				{
					Triangle test = triangles.front();
					triangles.pop_front();
					newTriangles--;

					switch (p)
					{
						//Top edge of the screen
						case 0: trisToAdd = test.ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, clipped[0], clipped[1]); break;
						//Bottom edge of the screen
						case 1: trisToAdd = test.ClipAgainstPlane({ 0.0f, (float)GetScreenHeight() - 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, clipped[0], clipped[1]); break;
						//Left edge of the screen
						case 2: trisToAdd = test.ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, clipped[0], clipped[1]); break;
						//Right edge of the screen
						case 3: trisToAdd = test.ClipAgainstPlane({ (float)GetScreenWidth() - 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, clipped[0], clipped[1]); break;
					}

					for (int w = 0; w < trisToAdd; w++)
						triangles.push_back(clipped[w]);
				}
				newTriangles = triangles.size();
			}

			//Draw each triangle that we've still got after clipping
			for (auto &t : triangles)
			{
				DrawTexturedTriangle(
					t.vertices[0].x, t.vertices[0].y, t.textures[0].u, t.textures[0].v, t.textures[0].w,
					t.vertices[1].x, t.vertices[1].y, t.textures[1].u, t.textures[1].v, t.textures[1].w,
					t.vertices[2].x, t.vertices[2].y, t.textures[2].u, t.textures[2].v, t.textures[2].w,
					sprTexture
				);

				//Draws filled, untextured model (for debug purposes mostly)
				/*DrawFilledTriangle(
					t.vertices[0].x, t.vertices[0].y,
					t.vertices[1].x, t.vertices[1].y,
					t.vertices[2].x, t.vertices[2].y,
					t.symbol, t.color
				);*/

				//Draws wireframe of the model (for debug purposes)
				/*DrawTriangle(
					t.vertices[0].x, t.vertices[0].y,
					t.vertices[1].x, t.vertices[1].y,
					t.vertices[2].x, t.vertices[2].y,
					PIXEL_SOLID, FG_WHITE
				);*/
			}
		}

		return true;
	}

	void DrawTexturedTriangle(
		int x0, int y0, float u0, float v0, float w0,
		int x1, int y1, float u1, float v1, float w1,
		int x2, int y2, float u2, float v2, float w2,
		Sprite *texture)
	{
		if (y1 < y0)
		{
			std::swap(y1, y0);
			std::swap(x1, x0);
			std::swap(u1, u0);
			std::swap(v1, v0);
			std::swap(w1, w0);
		}

		if (y2 < y0)
		{
			std::swap(y2, y0);
			std::swap(x2, x0);
			std::swap(u2, u0);
			std::swap(v2, v0);
			std::swap(w2, w0);
		}

		if (y2 < y1)
		{
			std::swap(y2, y1);
			std::swap(x2, x1);
			std::swap(u2, u1);
			std::swap(v2, v1);
			std::swap(w2, w1);
		}

		int dyA = y1 - y0;
		int dxA = x1 - x0;
		float duA = u1 - u0;
		float dvA = v1 - v0;
		float dwA = w1 - w0;

		int dyB = y2 - y0;
		int dxB = x2 - x0;
		float duB = u2 - u0;
		float dvB = v2 - v0;
		float dwB = w2 - w0;

		float texU, texV, texW;

		float 
			dxStepA = 0.0f, dxStepB = 0.0f,
			duStepA = 0.0f, duStepB = 0.0f,
			dvStepA = 0.0f, dvStepB = 0.0f,
			dwStepA = 0.0f, dwStepB = 0.0f;

		if (dyA != 0)
		{
			float dyInv = 1.0f / (float)abs(dyA);
			dxStepA = dxA * dyInv;
			duStepA = duA * dyInv;
			dvStepA = dvA * dyInv;
			dwStepA = dwA * dyInv;
		}
		
		if (dyB != 0)
		{
			float dyInv = 1.0f / (float)abs(dyB);
			dxStepB = dxB * dyInv;
			duStepB = duB * dyInv;
			dvStepB = dvB * dyInv;
			dwStepB = dwB * dyInv;
		}

		if (dyA != 0)
		{
			for (int i = y0; i <= y1; i++)
			{
				int ax = x0 + (float)(i - y0) * dxStepA;
				int bx = x0 + (float)(i - y0) * dxStepB;

				float su = u0 + (float)(i - y0) * duStepA;
				float sv = v0 + (float)(i - y0) * dvStepA;
				float sw = w0 + (float)(i - y0) * dwStepA;

				float eu = u0 + (float)(i - y0) * duStepB;
				float ev = v0 + (float)(i - y0) * dvStepB;
				float ew = w0 + (float)(i - y0) * dwStepB;

				if (ax > bx)
				{
					std::swap(ax, bx);
					std::swap(su, eu);
					std::swap(sv, ev);
					std::swap(sw, ew);
				}

				texU = su;
				texV = sv;
				texW = sw;

				float tStep = 1.0f / ((float)(bx - ax));
				float t = 0.0f;

				for (int j = ax; j < bx; j++)
				{
					texU = (1.0f - t) * su + t * eu;
					texV = (1.0f - t) * sv + t * ev;
					texW = (1.0f - t) * sw + t * ew;

					if (texW > depthBuffer[GetScreenWidth() * i + j])
					{
						float wInverse = 1.0f / texW;
						DrawPoint(j, i, texture->SampleCharacter(texU * wInverse, texV * wInverse), texture->SampleColor(texU * wInverse, texV * wInverse));
						depthBuffer[GetScreenWidth() * i + j] = texW;
					}
					t += tStep;
				}
			}
		}

		dyA = y2 - y1;
		dxA = x2 - x1;
		duA = u2 - u1;
		dvA = v2 - v1;
		dwA = w2 - w1;

		duStepA = 0, dvStepA = 0;

		if (dyA != 0)
		{
			float dyInv = 1.0f / (float)abs(dyA);
			dxStepA = dxA * dyInv;
			duStepA = duA * dyInv;
			dvStepA = dvA * dyInv;
			dwStepA = dwA * dyInv;
		}

		if (dyB) dxStepB = dxB / (float)abs(dyB);

		if (dyA != 0)
		{
			for (int i = y1; i <= y2; i++)
			{
				int ax = x1 + (float)(i - y1) * dxStepA;
				int bx = x0 + (float)(i - y0) * dxStepB;

				float su = u1 + (float)(i - y1) * duStepA;
				float sv = v1 + (float)(i - y1) * dvStepA;
				float sw = w1 + (float)(i - y1) * dwStepA;

				float eu = u0 + (float)(i - y0) * duStepB;
				float ev = v0 + (float)(i - y0) * dvStepB;
				float ew = w0 + (float)(i - y0) * dwStepB;

				if (ax > bx)
				{
					std::swap(ax, bx);
					std::swap(su, eu);
					std::swap(sv, ev);
					std::swap(sw, ew);
				}

				texU = su;
				texV = sv;
				texW = sw;

				float tStep = 1.0f / ((float)(bx - ax));
				float t = 0.0f;

				for (int j = ax; j < bx; j++)
				{
					texU = (1.0f - t) * su + t * eu;
					texV = (1.0f - t) * sv + t * ev;
					texW = (1.0f - t) * sw + t * ew;

					if (texW > depthBuffer[GetScreenWidth() * i + j])
					{
						float wInverse = 1.0f / texW;
						DrawPoint(j, i, texture->SampleCharacter(texU * wInverse, texV * wInverse), texture->SampleColor(texU * wInverse, texV * wInverse));
						depthBuffer[GetScreenWidth() * i + j] = texW;
					}
					t += tStep;
				}
			}
		}
	}

};

int main()
{
	ConsoleEngine3D engine;
	if (engine.ConstructScreen(256, 240, 4, 4))
		engine.Start();

	return 0;
}