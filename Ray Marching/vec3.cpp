/********************************
* Zared Hollabaugh				*
* February 6 2015 GCC COMP 361  *
* 								*
********************************/

#include "vec3.h"

vec3::vec3() { }

vec3::vec3(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

float vec3::dot(vec3 a)
{
	float sum = 0.0f;
	sum+= x*a.x;
	sum += y*a.y;
	sum += z*a.z;

	return sum;
}

vec3 vec3::cross(vec3 a)
{
	vec3 c;

	c.x = y*a.z-z*a.y;
	c.y = z*a.x-x*a.z;
	c.z = x*a.y-y*a.x;

	return c;
}

vec3 vec3::operator+(vec3& a) const 
{
	return vec3(x + a.x, y + a.y, z + a.z);
}


vec3 vec3::operator-(vec3& a) const 
{
	return vec3(x - a.x, y - a.y, z - a.z);
}

vec3 vec3::operator*(float a) const 
{
	return vec3(x * a, y * a, z * a);
}

vec3 vec3::operator*(vec3 a) const 
{
	return vec3(x * a.x, y * a.y, z * a.y);
}

vec3 vec3::operator/(float a)
{
	return this->operator*(1/a);
}

vec3 vec3::operator()(float a)
{
	x = a;
	y = a;
	z = a;

	return vec3();
}

vec3 vec3::normalize()
{
	return this->operator/(this->magnitude());
}

float vec3::magnitude()
{
	return sqrt(x*x+y*y+z*z);
}


