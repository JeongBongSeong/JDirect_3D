#pragma once
#include "JMatrix.h"

enum JCollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
struct JRect2D
{
	JVector2 vMin;
	JVector2 vMax;
	JVector2 vMiddle;
	JVector2 size;
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
	JRect2D(JVector2 vMin, JVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	JRect2D(JVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + JVector2(w, h);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
struct JRect
{
	JVector2 vMin;
	JVector2 vMax;
	JVector2 vMiddle;
	JVector2 size;
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
	JRect(JVector2 vMin, JVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	JRect(JVector2 pos, float w, float h)
	{
		vMiddle = pos;
		this->vMin = vMiddle - JVector2(w/2.0f, h/2.0f);
		this->vMax = vMiddle + JVector2(w / 2.0f, h / 2.0f);
		this->size.x = w;
		this->size.y = h;
	}
};
struct JBox
{
	JVector3 vMin;
	JVector3 vMax;
	JVector3 vMiddle;
	JVector3 size;
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
	JBox(JVector3 vMin, JVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	JBox(JVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + JVector3(w, h, q);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
class JCollision
{
public:
	static bool   RectToPoint(JRect rt, int x, int y);
	static bool   RectToPoint(JRect rt, JVector2 v);
	static JCollisionResult	RectToRect(JRect rt1, JRect rt2);
	static JCollisionResult	ToRect(JRect rt1, JRect rt2);
	static JRect  UnionRect(JRect rt1, JRect rt2);
	static bool  IntersecJRect(JRect rt1, JRect rt2, JRect* rt);

	static bool   BoxToPoint(JBox rt, int x, int y, int z);
	static bool   BoxToPoint(JBox rt, JVector3 v);
	static JCollisionResult    BoxToBox(JBox, JBox);
	static JBox   UnionBox(JBox rt1, JBox rt2);
	static bool  IntersectBox(JBox rt1, JBox rt2, JBox* rt);
};