#include "JVector2.h"
JVector2::JVector2()
{
	x = y = 0.0f;
}
JVector2::JVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
JVector2::JVector2(const JVector2& v)
{
	x = v.x;
	y = v.y;
}
JVector2 JVector2::operator + (const JVector2& v)
{
	JVector2 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	return ret;
}
JVector2 JVector2::operator - (const JVector2& v)
{
	JVector2 ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	return ret;
}
JVector2 JVector2::operator * (float fValue)
{
	JVector2 ret;
	ret.x = this->x * fValue;
	ret.y = this->y * fValue;
	return ret;
}
JVector2 JVector2::operator / (float fValue)
{
	JVector2 ret;
	ret.x = this->x / fValue;
	ret.y = this->y / fValue;
	return ret;
}
JVector2 JVector2::operator += (const JVector2& v)
{
	JVector2 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	return ret;
}
JVector2 JVector2::operator -= (const JVector2& v)
{
	JVector2 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	return ret;
}
bool JVector2::operator == (const JVector2& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return true;
		}
	}
	return false;
}
bool JVector2::operator != (const JVector2& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return false;
		}
	}
	return true;
}

JVector2 JVector2::Normal()
{
	JVector2 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	return ret;
}
JVector2 JVector2::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	return *this;
}
JVector2 Normalize(JVector2& v)
{
	JVector2 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	return ret;
}
//
float JVector2::Length()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}

//두 백터의 거리 반환
float JVector2::Distance(JVector2& v)
{
	float fDist = (*this - v).Length();
	return fDist;
}
