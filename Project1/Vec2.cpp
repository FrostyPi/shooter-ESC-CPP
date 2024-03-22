#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin)
{

}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y+ rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator / (const float val) const
{	
	return Vec2(x / val, y / val);
}

Vec2 Vec2::operator * (const float val) const
{ 
	return Vec2(x*val, y*val);
}

bool Vec2::operator == (const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	return !(x == rhs.x && y == rhs.y);
}

void Vec2::operator += (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
	x *= val;
	y *= val;
}

void Vec2::operator /= (const float val)
{
	x /= val;
	y /= val;
}


float Vec2::dist2(const Vec2 & rhs) const
{
	int nx = x - rhs.x;
	int ny = y - rhs.y;

	return pow(nx, 2) + pow(ny, 2);
}

float Vec2::length() const
{

	return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::normalize()
{
	return Vec2(x / length(), y / length());
}
  















