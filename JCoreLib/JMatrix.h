#pragma once
#include "JVector3.h"
struct float4x4
{
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};
class JMatrix : public float4x4
{
public:
	JMatrix operator * (JMatrix const& Matrix);
	void XRotate(float fRadian);
	void YRotate(float fRadian);
	void ZRotate(float fRadian);
	void Translation(const JVector3& v); 
	void Translation(float x, float y, float z);
	void Scale(const JVector3& v);
	void Scale(float x, float y, float z);
	JMatrix Transpose();
	JMatrix ViewLookAt(JVector3& vPosition, JVector3& vTarget,	JVector3& vUp);
	JMatrix CreateViewLook(JVector3& vPosition, JVector3& vTarget, JVector3& vUp);
	JMatrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect); // width / heght
public:
	void Identity()
	{
		_11 = _12 = _13 = _14 = 0.0f;
		_21 = _22 = _23 = _24 = 0.0f;
		_31 = _32 = _33 = _34 = 0.0f;
		_41 = _42 = _43 = _44 = 0.0f;
		_11 = _22 = _33 = _44 = 1.0f;
	}
public:
	JMatrix()
	{
		Identity();
	};
};

