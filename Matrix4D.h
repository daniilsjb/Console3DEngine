#pragma once

#include "Vector3D.h"

struct Matrix4D
{
	float m[4][4] = { 0.0f };

	Matrix4D() {}

	Matrix4D(
		float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23,
		float n30, float n31, float n32, float n33)
	{
		m[0][0] = n00; m[0][1] = n01; m[0][2] = n02; m[0][3] = n03;
		m[1][0] = n10; m[1][1] = n11; m[1][2] = n12; m[1][3] = n13;
		m[2][0] = n20; m[2][1] = n21; m[2][2] = n22; m[2][3] = n23;
		m[3][0] = n30; m[3][1] = n31; m[3][2] = n32; m[3][3] = n33;
	}

	Matrix4D operator+(const Matrix4D &rhs)
	{
		Matrix4D r;

		r.m[0][0] = m[0][0] + rhs.m[0][0];
		r.m[0][1] = m[0][1] + rhs.m[0][1];
		r.m[0][2] = m[0][2] + rhs.m[0][2];
		r.m[0][3] = m[0][3] + rhs.m[0][3];

		r.m[1][0] = m[1][0] + rhs.m[1][0];
		r.m[1][1] = m[1][1] + rhs.m[1][1];
		r.m[1][2] = m[1][2] + rhs.m[1][2];
		r.m[1][3] = m[1][3] + rhs.m[1][3];

		r.m[2][0] = m[2][0] + rhs.m[2][0];
		r.m[2][1] = m[2][1] + rhs.m[2][1];
		r.m[2][2] = m[2][2] + rhs.m[2][2];
		r.m[2][3] = m[2][3] + rhs.m[2][3];

		r.m[3][0] = m[3][0] + rhs.m[3][0];
		r.m[3][1] = m[3][1] + rhs.m[3][1];
		r.m[3][2] = m[3][2] + rhs.m[3][2];
		r.m[3][3] = m[3][3] + rhs.m[3][3];

		return r;
	}

	Matrix4D operator+(const float rhs)
	{
		Matrix4D r;

		r.m[0][0] = m[0][0] + rhs;
		r.m[0][1] = m[0][1] + rhs;
		r.m[0][2] = m[0][2] + rhs;
		r.m[0][3] = m[0][3] + rhs;

		r.m[1][0] = m[1][0] + rhs;
		r.m[1][1] = m[1][1] + rhs;
		r.m[1][2] = m[1][2] + rhs;
		r.m[1][3] = m[1][3] + rhs;

		r.m[2][0] = m[2][0] + rhs;
		r.m[2][1] = m[2][1] + rhs;
		r.m[2][2] = m[2][2] + rhs;
		r.m[2][3] = m[2][3] + rhs;

		r.m[3][0] = m[3][0] + rhs;
		r.m[3][1] = m[3][1] + rhs;
		r.m[3][2] = m[3][2] + rhs;
		r.m[3][3] = m[3][3] + rhs;

		return r;
	}

	Matrix4D operator-(const Matrix4D &rhs)
	{
		Matrix4D r;

		r.m[0][0] = m[0][0] - rhs.m[0][0];
		r.m[0][1] = m[0][1] - rhs.m[0][1];
		r.m[0][2] = m[0][2] - rhs.m[0][2];
		r.m[0][3] = m[0][3] - rhs.m[0][3];

		r.m[1][0] = m[1][0] - rhs.m[1][0];
		r.m[1][1] = m[1][1] - rhs.m[1][1];
		r.m[1][2] = m[1][2] - rhs.m[1][2];
		r.m[1][3] = m[1][3] - rhs.m[1][3];

		r.m[2][0] = m[2][0] - rhs.m[2][0];
		r.m[2][1] = m[2][1] - rhs.m[2][1];
		r.m[2][2] = m[2][2] - rhs.m[2][2];
		r.m[2][3] = m[2][3] - rhs.m[2][3];

		r.m[3][0] = m[3][0] - rhs.m[3][0];
		r.m[3][1] = m[3][1] - rhs.m[3][1];
		r.m[3][2] = m[3][2] - rhs.m[3][2];
		r.m[3][3] = m[3][3] - rhs.m[3][3];

		return r;
	}

	Matrix4D operator-(const float rhs)
	{
		Matrix4D r;

		r.m[0][0] = m[0][0] - rhs;
		r.m[0][1] = m[0][1] - rhs;
		r.m[0][2] = m[0][2] - rhs;
		r.m[0][3] = m[0][3] - rhs;

		r.m[1][0] = m[1][0] - rhs;
		r.m[1][1] = m[1][1] - rhs;
		r.m[1][2] = m[1][2] - rhs;
		r.m[1][3] = m[1][3] - rhs;

		r.m[2][0] = m[2][0] - rhs;
		r.m[2][1] = m[2][1] - rhs;
		r.m[2][2] = m[2][2] - rhs;
		r.m[2][3] = m[2][3] - rhs;

		r.m[3][0] = m[3][0] - rhs;
		r.m[3][1] = m[3][1] - rhs;
		r.m[3][2] = m[3][2] - rhs;
		r.m[3][3] = m[3][3] - rhs;

		return r;
	}

	Matrix4D operator*(const Matrix4D &rhs)
	{
		Matrix4D r;

		r.m[0][0] = m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0] + m[0][2] * rhs.m[2][0] + m[0][3] * rhs.m[3][0];
		r.m[0][1] = m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1] + m[0][2] * rhs.m[2][1] + m[0][3] * rhs.m[3][1];
		r.m[0][2] = m[0][0] * rhs.m[0][2] + m[0][1] * rhs.m[1][2] + m[0][2] * rhs.m[2][2] + m[0][3] * rhs.m[3][2];
		r.m[0][3] = m[0][0] * rhs.m[0][3] + m[0][1] * rhs.m[1][3] + m[0][2] * rhs.m[2][3] + m[0][3] * rhs.m[3][3];

		r.m[1][0] = m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0] + m[1][2] * rhs.m[2][0] + m[1][3] * rhs.m[3][0];
		r.m[1][1] = m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1] + m[1][2] * rhs.m[2][1] + m[1][3] * rhs.m[3][1];
		r.m[1][2] = m[1][0] * rhs.m[0][2] + m[1][1] * rhs.m[1][2] + m[1][2] * rhs.m[2][2] + m[1][3] * rhs.m[3][2];
		r.m[1][3] = m[1][0] * rhs.m[0][3] + m[1][1] * rhs.m[1][3] + m[1][2] * rhs.m[2][3] + m[1][3] * rhs.m[3][3];

		r.m[2][0] = m[2][0] * rhs.m[0][0] + m[2][1] * rhs.m[1][0] + m[2][2] * rhs.m[2][0] + m[2][3] * rhs.m[3][0];
		r.m[2][1] = m[2][0] * rhs.m[0][1] + m[2][1] * rhs.m[1][1] + m[2][2] * rhs.m[2][1] + m[2][3] * rhs.m[3][1];
		r.m[2][2] = m[2][0] * rhs.m[0][2] + m[2][1] * rhs.m[1][2] + m[2][2] * rhs.m[2][2] + m[2][3] * rhs.m[3][2];
		r.m[2][3] = m[2][0] * rhs.m[0][3] + m[2][1] * rhs.m[1][3] + m[2][2] * rhs.m[2][3] + m[2][3] * rhs.m[3][3];

		r.m[3][0] = m[3][0] * rhs.m[0][0] + m[3][1] * rhs.m[1][0] + m[3][2] * rhs.m[2][0] + m[3][3] * rhs.m[3][0];
		r.m[3][1] = m[3][0] * rhs.m[0][1] + m[3][1] * rhs.m[1][1] + m[3][2] * rhs.m[2][1] + m[3][3] * rhs.m[3][1];
		r.m[3][2] = m[3][0] * rhs.m[0][2] + m[3][1] * rhs.m[1][2] + m[3][2] * rhs.m[2][2] + m[3][3] * rhs.m[3][2];
		r.m[3][3] = m[3][0] * rhs.m[0][3] + m[3][1] * rhs.m[1][3] + m[3][2] * rhs.m[2][3] + m[3][3] * rhs.m[3][3];

		return r;
	}

	Matrix4D operator*(const float rhs)
	{
		Matrix4D r;

		r.m[0][0] = m[0][0] * rhs;
		r.m[0][1] = m[0][1] * rhs;
		r.m[0][2] = m[0][2] * rhs;
		r.m[0][3] = m[0][3] * rhs;

		r.m[1][0] = m[1][0] * rhs;
		r.m[1][1] = m[1][1] * rhs;
		r.m[1][2] = m[1][2] * rhs;
		r.m[1][3] = m[1][3] * rhs;

		r.m[2][0] = m[2][0] * rhs;
		r.m[2][1] = m[2][1] * rhs;
		r.m[2][2] = m[2][2] * rhs;
		r.m[2][3] = m[2][3] * rhs;

		r.m[3][0] = m[3][0] * rhs;
		r.m[3][1] = m[3][1] * rhs;
		r.m[3][2] = m[3][2] * rhs;
		r.m[3][3] = m[3][3] * rhs;

		return r;
	}

	Vector3D operator*(const Vector3D &v)
	{
		Vector3D result;

		result.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + v.w * m[3][0];
		result.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + v.w * m[3][1];
		result.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + v.w * m[3][2];
		result.w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + v.w * m[3][3];

		return result;
	}

	Matrix4D operator/(const float rhs)
	{
		Matrix4D r;
		float inverse = 1.0f / rhs;

		r.m[0][0] = m[0][0] * inverse;
		r.m[0][1] = m[0][1] * inverse;
		r.m[0][2] = m[0][2] * inverse;
		r.m[0][3] = m[0][3] * inverse;

		r.m[1][0] = m[1][0] * inverse;
		r.m[1][1] = m[1][1] * inverse;
		r.m[1][2] = m[1][2] * inverse;
		r.m[1][3] = m[1][3] * inverse;

		r.m[2][0] = m[2][0] * inverse;
		r.m[2][1] = m[2][1] * inverse;
		r.m[2][2] = m[2][2] * inverse;
		r.m[2][3] = m[2][3] * inverse;

		r.m[3][0] = m[3][0] * inverse;
		r.m[3][1] = m[3][1] * inverse;
		r.m[3][2] = m[3][2] * inverse;
		r.m[3][3] = m[3][3] * inverse;

		return r;
	}

	Matrix4D& operator+=(const Matrix4D &rhs)
	{
		*this = (*this + rhs);
		return *this;
	}

	Matrix4D& operator+=(const float rhs)
	{
		*this = (*this + rhs);
		return *this;
	}

	Matrix4D& operator-=(const Matrix4D &rhs)
	{
		*this = (*this - rhs);
		return *this;
	}

	Matrix4D& operator-=(const float rhs)
	{
		*this = (*this - rhs);
		return *this;
	}

	Matrix4D& operator*=(const Matrix4D &rhs)
	{
		*this = (*this * rhs);
		return *this;
	}

	Matrix4D& operator*=(const float rhs)
	{
		*this = (*this * rhs);
		return *this;
	}

	Matrix4D& operator/=(const float rhs)
	{
		*this = (*this / rhs);
		return *this;
	}

	void Indentity()
	{
		Matrix4D identity;

		identity.m[0][0] = 1.0f;
		identity.m[1][1] = 1.0f;
		identity.m[2][2] = 1.0f;
		identity.m[3][3] = 1.0f;

		*this = identity;
	}

	void Projection(float FoV, float aspectRatio, float zNear, float zFar)
	{
		float FoVRadians = 1.0f / tanf(FoV * 0.5f / 180.0f * 3.14159f);

		float q = zFar / (zFar - zNear);

		Matrix4D projection;

		projection.m[0][0] = aspectRatio * FoVRadians;
		projection.m[1][1] = FoVRadians;
		projection.m[2][2] = q;
		projection.m[3][2] = -q * zNear;
		projection.m[2][3] = 1.0f;

		*this = projection;
	}

	void Translation(float x, float y, float z)
	{
		Matrix4D translation;

		translation.m[0][0] = 1.0f;
		translation.m[1][1] = 1.0f;
		translation.m[2][2] = 1.0f;
		translation.m[3][3] = 1.0f;

		translation.m[3][0] = x;
		translation.m[3][1] = y;
		translation.m[3][2] = z;

		*this = translation;
	}

	void RotationX(float theta)
	{
		Matrix4D rotation;

		rotation.m[0][0] = 1.0f;
		rotation.m[1][1] = cosf(theta);
		rotation.m[1][2] = sinf(theta);
		rotation.m[2][1] = -sinf(theta);
		rotation.m[2][2] = cosf(theta);
		rotation.m[3][3] = 1.0f;

		*this = rotation;
	}

	void RotationY(float theta)
	{
		Matrix4D rotation;

		rotation.m[0][0] = cosf(theta);
		rotation.m[0][2] = sinf(theta);
		rotation.m[1][1] = 1.0f;
		rotation.m[2][0] = -sinf(theta);
		rotation.m[2][2] = cosf(theta);
		rotation.m[3][3] = 1.0f;

		*this = rotation;
	}

	void RotationZ(float theta)
	{
		Matrix4D rotation;

		rotation.m[0][0] = cosf(theta);
		rotation.m[0][1] = sinf(theta);
		rotation.m[1][0] = -sinf(theta);
		rotation.m[1][1] = cosf(theta);
		rotation.m[2][2] = 1.0f;
		rotation.m[3][3] = 1.0f;

		*this = rotation;
	}

	void PointAt(Vector3D &pos, Vector3D &target, Vector3D &up)
	{
		Vector3D newForward = target - pos;
		newForward.Normalize();

		Vector3D a = newForward * (up.Dot(newForward));
		Vector3D newUp = up - a;
		newUp.Normalize();

		Vector3D newRight = newUp.Cross(newForward);

		Matrix4D pointAt;

		pointAt.m[0][0] = newRight.x; pointAt.m[0][1] = newRight.y; pointAt.m[0][2] = newRight.z; pointAt.m[0][3] = 0.0f;
		pointAt.m[1][0] = newUp.x; pointAt.m[1][1] = newUp.y; pointAt.m[1][2] = newUp.z; pointAt.m[1][3] = 0.0f;
		pointAt.m[2][0] = newForward.x; pointAt.m[2][1] = newForward.y; pointAt.m[2][2] = newForward.z; pointAt.m[2][3] = 0.0f;
		pointAt.m[3][0] = pos.x; pointAt.m[3][1] = pos.y; pointAt.m[3][2] = pos.z; pointAt.m[3][3] = 1.0f;

		*this = pointAt;
	}

	//Dirty hack that only works for rotation and translation matrices
	void QuickInverse(Matrix4D &m)
	{
		Matrix4D inverse;

		inverse.m[0][0] = m.m[0][0]; inverse.m[0][1] = m.m[1][0]; inverse.m[0][2] = m.m[2][0]; inverse.m[0][3] = 0.0f;
		inverse.m[1][0] = m.m[0][1]; inverse.m[1][1] = m.m[1][1]; inverse.m[1][2] = m.m[2][1]; inverse.m[1][3] = 0.0f;
		inverse.m[2][0] = m.m[0][2]; inverse.m[2][1] = m.m[1][2]; inverse.m[2][2] = m.m[2][2]; inverse.m[2][3] = 0.0f;
		inverse.m[3][0] = -(m.m[3][0] * inverse.m[0][0] + m.m[3][1] * inverse.m[1][0] + m.m[3][2] * inverse.m[2][0]);
		inverse.m[3][1] = -(m.m[3][0] * inverse.m[0][1] + m.m[3][1] * inverse.m[1][1] + m.m[3][2] * inverse.m[2][1]);
		inverse.m[3][2] = -(m.m[3][0] * inverse.m[0][2] + m.m[3][1] * inverse.m[1][2] + m.m[3][2] * inverse.m[2][2]);
		inverse.m[3][3] = 1.0f;

		*this = inverse;
	}

};