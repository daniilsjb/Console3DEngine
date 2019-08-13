#pragma once

#include <cmath>

//The W component is required to enable perspective, technically making this a 4D vector
struct Vector3D
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	Vector3D operator+(const Vector3D &rhs)
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vector3D operator+(const float rhs)
	{
		return { x + rhs, y + rhs, z + rhs };
	}

	Vector3D operator-(const Vector3D &rhs)
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	Vector3D operator-(const float rhs)
	{
		return { x - rhs, y - rhs, z - rhs };
	}

	Vector3D operator*(const float rhs)
	{
		return { x * rhs, y * rhs, z * rhs };
	}

	Vector3D operator/(const float rhs)
	{
		float inverse = 1.0f / rhs;
		return { x * inverse, y * inverse, z * inverse };
	}

	Vector3D& operator+=(const Vector3D &rhs)
	{
		*this = (*this + rhs);
		return *this;
	}

	Vector3D& operator-=(const Vector3D &rhs)
	{
		*this = (*this - rhs);
		return *this;
	}

	Vector3D& operator*=(const float rhs)
	{
		*this = (*this * rhs);
		return *this;
	}

	Vector3D& operator/=(const float rhs)
	{
		*this = (*this / rhs);
		return *this / rhs;
	}

	float Dot(Vector3D &rhs)
	{
		return (x * rhs.x + y * rhs.y + z * rhs.z);
	}

	Vector3D Cross(Vector3D &rhs)
	{
		return { y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x };
	}

	float Magnitude()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	Vector3D Normalized()
	{
		return *this / Magnitude();
	}

	void Normalize()
	{
		*this = Normalized();
	}

	void IntersectPlane(Vector3D &planeP, Vector3D &planeN, Vector3D &lineStart, Vector3D &lineEnd, float &t)
	{
		Vector3D intersection;

		planeN.Normalize();
		float planeD = -planeN.Dot(planeP);
		float ad = lineStart.Dot(planeN);
		float bd = lineEnd.Dot(planeN);
		t = (-planeD - ad) / (bd - ad);
		Vector3D lineStartToEnd = lineEnd - lineStart;
		Vector3D lineToIntersect = lineStartToEnd * t;
		intersection = lineStart + lineToIntersect;

		*this = intersection;
	}

};