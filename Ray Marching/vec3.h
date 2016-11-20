/********************************
* Zared Hollabaugh				*
* February 6 2015 GCC COMP 361  *
* 								*
********************************/

#pragma once
#include <math.h>
 
class vec3
{
public:
	float x,y,z;
	vec3();
	vec3(float x, float y, float z);
	float dot(vec3 a);
	vec3 cross(vec3 a);
	float magnitude();
	vec3 normalize();

	vec3 operator+(vec3 &a) const;
	vec3 operator-(vec3 &a) const;
	vec3 operator*(float a) const;
	vec3 operator*(vec3 a) const;
	vec3 operator/(float c);
	vec3 operator()(float a);
};

struct ivec3 {
	int x;
	int y;
	int z;
};

