#pragma once
#include <iostream>
#include <math.h>

struct JFloat2
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
};

struct JFloat4
{
	union
	{
		struct { float x, y, z, w; };
		float v[4];
	};
};

class JVector2 : public JFloat2
{
public:
	JVector2();
	JVector2(float x, float y);
	JVector2(const JVector2& v);
public:
	JVector2 operator + (const JVector2& v);
	JVector2 operator - (const JVector2& v);
	JVector2 operator * (float fValue);
	JVector2 operator / (float fValue);
	JVector2 operator += (const JVector2& v);
	JVector2 operator -= (const JVector2& v);
	bool operator == (const JVector2& v);
	bool operator != (const JVector2& v);
	//
	JVector2 Normalize();
	JVector2 Normal();
	friend JVector2 Normalize(JVector2& v);
	//
	float Length();
	float Distance(JVector2& v);
};

class JVector4 : public JFloat4
{
public:
	JVector4() {
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		v[3] = 0.0f;
	};
	JVector4(float x, float y, float z, float w) {
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
	}
	JVector4(const JVector4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
};