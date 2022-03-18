#include "JMatrix.h"

JMatrix JMatrix::operator * (JMatrix const& Matrix)
{
	JMatrix OutMatrix;
	for (int iColumn = 0; iColumn < 4; iColumn++)
	{
		for (int iRow = 0; iRow < 4; iRow++)
		{
			OutMatrix.m[iRow][iColumn] = m[iRow][0] * Matrix.m[0][iColumn] +
				m[iRow][1] * Matrix.m[1][iColumn] +
				m[iRow][2] * Matrix.m[2][iColumn] +
				m[iRow][3] * Matrix.m[3][iColumn];
		}
	}
	return OutMatrix;
}

void JMatrix::XRotate(float fRadian)
{
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);

	_22 = fCos;
	_23 = fSin;
	_32 = -fSin;
	_33 = fCos;
}
void JMatrix::YRotate(float fRadian)
{
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);

	_11 = fCos;
	_13 = -fSin;
	_31 = fSin;
	_33 = fCos;
}
void JMatrix::ZRotate(float fRadian)
{
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);

	_11 = fCos;
	_12 = fSin;
	_21 = -fSin;
	_22 = fCos;
}
void JMatrix::Translation(const JVector3& v)
{
	_41 = v.x;
	_42 = v.y;
	_43 = v.z;
}

void JMatrix::Translation(float x, float y, float z)
{
	_41 = x;
	_42 = y;
	_43 = z;
}
void JMatrix::Scale(const JVector3& v)
{
	_11 = v.x;
	_22 = v.y;
	_33 = v.z;
}
void JMatrix::Scale(float x, float y, float z)
{
	_11 = x;
	_22 = y;
	_33 = z;
}
JMatrix JMatrix::Transpose()
{
	JMatrix matrix;
	matrix._11 = _11; matrix._12 = _21; matrix._13 = _31; matrix._14 = _41;
	matrix._21 = _12; matrix._22 = _22; matrix._23 = _32; matrix._24 = _42;
	matrix._31 = _13; matrix._32 = _23; matrix._33 = _33; matrix._34 = _43;
	matrix._41 = _14; matrix._42 = _24; matrix._43 = _34; matrix._44 = _44;
	return matrix;
}

JMatrix JMatrix::ViewLookAt(JVector3& vPosition, JVector3& vTarget, JVector3& vUp)
{
	JMatrix matrix;
	JVector3 vDirection = (vTarget - vPosition).Normal();		// Z Axis
	JVector3 vRightVector = (vUp ^ vDirection).Normal();		// X Axis
	JVector3 vUpVector = (vDirection ^ vRightVector).Normal();	// Y Axis

	_11 = vRightVector.x;	_12 = vUpVector.x;	_13 = vDirection.x;
	_21 = vRightVector.y;	_22 = vUpVector.y;	_23 = vDirection.y;
	_31 = vRightVector.z;	_32 = vUpVector.z;	_33 = vDirection.z;

	_41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
	_42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
	_43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
	memcpy((void*)&matrix, this, 16 * sizeof(float));
	return matrix;
}

JMatrix JMatrix::CreateViewLook(JVector3& vPosition, JVector3& vTarget, JVector3& vUp)
{
	JMatrix matrix;
	JVector3 vDirection = vTarget - vPosition;
	vDirection = vDirection.Normal();//z
	float fDot = vUp | vDirection;
	// 직교의 근사화 작업
	JVector3 vUpVector = vUp - (vDirection * fDot);
	vUpVector = vUpVector.Normal();
	JVector3 vRightVector = vUpVector ^ vDirection;

	_11 = vRightVector.x;	_12 = vUpVector.x;	_13 = vDirection.x;
	_21 = vRightVector.y;	_22 = vUpVector.y;	_23 = vDirection.y;
	_31 = vRightVector.z;	_32 = vUpVector.z;	_33 = vDirection.z;
	_41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
	_42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
	_43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
	memcpy((void*)&matrix, this, 16 * sizeof(float));
	return matrix;
}
JMatrix JMatrix::PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect)
{
	float    h, w, Q;

	h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
	w = h / Aspect;

	Q = fFarPlane / (fFarPlane - fNearPlane);

	JMatrix ret;
	memset(this, 0, sizeof(JMatrix));

	_11 = w;
	_22 = h;
	_33 = Q;
	_43 = -Q * fNearPlane;
	_34 = 1;

	memcpy((void*)&ret, this, 16 * sizeof(float));
	return ret;
}