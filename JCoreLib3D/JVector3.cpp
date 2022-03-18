#include "JVector3.h"
JVector3::JVector3()
{
	x = y = z = 0.0f;
}
JVector3::JVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
JVector3::JVector3(const JVector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
void JVector3::operator += (const JVector3& v)
{
	JVector3 ret;
	this->x = this->x + v.x;
	this->y = this->y + v.y;
	this->z = this->z + v.z;
}
void JVector3::operator += (const JVector3& v)
{
	JVector3 ret;
	this->x = this->x + v.x;
	this->y = this->y + v.y;
	this->z = this->z + v.z;
}
JVector3 JVector3::operator + (const JVector3& v)
{
	JVector3 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	ret.z = this->z + v.z;
	return ret;
}
JVector3 JVector3::operator - (const JVector3& v)
{
	JVector3 ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	ret.z = this->z - v.z;
	return ret;
}
JVector3 JVector3::operator * (float fValue)
{
	this->x *= fValue;
	this->y *= fValue;
	this->z *= fValue;
	return *this;
}
JVector3 JVector3::operator / (float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	this->z /= fValue;
	return *this;
}
bool JVector3::operator == (const JVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return true;
			}
		}
	}
	return false;
}
bool JVector3::operator != (const JVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return false;
			}
		}
	}
	return true;
}

JVector3 JVector3::Normal()
{
	JVector3 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	ret.z = z * length;
	return ret;
}
JVector3 JVector3::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	z *= length;
	return *this;
}
JVector3 Normalize(JVector3& v)
{
	JVector3 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	ret.z = v.z * length;
	return ret;
}
//
float JVector3::Length()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}

float JVector3::operator | (JVector3 const& v)
{
	return x * v.x + y + v.y + z + v.z;
}

JVector3 JVector3::operator ^ (JVector3 const& v)
{
	return JVector3((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.y));
}