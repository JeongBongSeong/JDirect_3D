#pragma once
#include "JMatrix.h"
#include "TMath.h"
enum JCollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
struct JRect2D
{
	T::TVector2 vMin;
	T::TVector2 vMax;
	T::TVector2 vMiddle;
	T::TVector2 size;
	bool operator == (const JRect2D& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	JRect2D() {};
	JRect2D(T::TVector2 vMin, T::TVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	JRect2D(T::TVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + T::TVector2(w, h);
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
struct JRect
{
	T::TVector2 vMin;
	T::TVector2 vMax;
	T::TVector2 vMiddle;
	T::TVector2 size;
	bool operator == (const JRect& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	JRect() {};
	JRect(T::TVector2 vMin, T::TVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	JRect(T::TVector2 pos, float w, float h)
	{
		vMiddle = pos;
		this->vMin = vMiddle - T::TVector2(w/2.0f, h/2.0f);
		this->vMax = vMiddle + T::TVector2(w / 2.0f, h / 2.0f);
		this->size.x = w;
		this->size.y = h;
	}
};
struct JBox
{
	T::TVector3 vList[8];
	T::TVector3 vMin;
	T::TVector3 vMax;
	T::TVector3 vMiddle;
	T::TVector3 vAxis[3];
	T::TVector3 size;
	bool operator == (const JBox& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	JBox() {};
	JBox(T::TVector3 vMin, T::TVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	JBox(T::TVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + T::TVector3(w, h, q);
		vMiddle = (vMax + vMin);
		vMiddle /= 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
struct JSphere
{
	T::TVector3 vMiddle;
	float fRadius;
	JSphere()
	{
		fRadius = 3.0f;
	}
};
class JCollision
{
public:
	static bool   SphereToPoint(JSphere rt, float x, float y, float z);
	static bool   SphereToPoint(JSphere rt, T::TVector3 v);
	static bool   RectToPoint(JRect rt, int x, int y);
	static bool   RectToPoint(JRect rt, T::TVector2 v);
	static JCollisionResult	RectToRect(JRect rt1, JRect rt2);
	static JCollisionResult	ToRect(JRect rt1, JRect rt2);
	static JRect  UnionRect(JRect rt1, JRect rt2);
	static bool  IntersecJRect(JRect rt1, JRect rt2, JRect* rt);

	static bool   BoxToPoint(JBox rt, int x, int y, int z);
	static bool   BoxToPoint(JBox rt, T::TVector3 v);
	static JCollisionResult    BoxToBox(JBox, JBox);
	static JBox   UnionBox(JBox rt1, JBox rt2);
	static bool  IntersectBox(JBox rt1, JBox rt2, JBox* rt);
};