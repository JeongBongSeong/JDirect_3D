#pragma once
#include "JVector2.h"
struct JFloat3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};
class JVector3 : public JFloat3
{
public:
	JVector3();
	JVector3(float x, float y, float z);
	JVector3(const JVector3& v);
public:
	void operator += (const JVector3& v);
	void operator -= (const JVector3& v);
	JVector3 operator + (const JVector3& v);
	JVector3 operator - (const JVector3& v);
	JVector3 operator * (float fValue);
	JVector3 operator / (float fValue);
	JVector3 operator | (JVector3 const& v);
	JVector3 operator ^ (JVector3 const& v);
	bool operator == (const JVector3& v);
	bool operator != (const JVector3& v);
	//
	JVector3 Normalize();
	JVector3 Normal();
	friend JVector3 Normalize(JVector3& v);
	//
	float Length();
};
