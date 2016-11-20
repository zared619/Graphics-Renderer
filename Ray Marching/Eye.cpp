/********************************
* Zared Hollabaugh				*
* February 6 2015 GCC COMP 361  *
* 								*
********************************/

#include "Eye.h"

void Eye::initialize()
{
	xpos = 0;
	ypos = 0;
	zpos =0;
	height = 0;
	width = 0;
	fovy = 0;
	vdir(0);
	uvec(0);
}

void Eye::setX(float pos)
{
	xpos = pos;
}

void Eye::setY(float pos)
{
	ypos = pos;
}

void Eye::setZ(float pos)
{
	zpos = pos;
}

void Eye::setHeight(float h)
{
	height = h;
}

void Eye::setWidth(float w)
{
	width = w;
}

void Eye::setFoV(float y)
{
	fovy = y;
}

void Eye::setVDir(vec3 vec)
{
	vdir = vec;
}

void Eye::setUVec(vec3 vec)
{
	uvec = vec;
}

vec3 Eye::normalize(vec3 a)
{
	float num = a.x*a.x + a.y*a.y + a.z*a.z;
	float length = sqrt(num);

	a.x = a.x/length;
	a.y = a.y/length;
	a.z = a.z/length;

	/*if(a.x < 0)
		a.x*=-1;
	if(a.y < 0)
		a.y*=-1;
	if(a.z < 0)
		a.z*=-1;*/

	return a;
}

vec3 Eye::generate(float x, float y)
{
	float theta = fovy/1.3f;
	vec3 n = vdir.normalize();
	vec3 u = n.cross(uvec).normalize();
	uvec = u.cross(n).normalize();
	vec3 v = uvec*((float)(tan(fovy*3.14159256/180)));
	vec3 h = u*v.magnitude()*(width/height);
	vec3 pos;
	pos.x = xpos;
	pos.y = ypos;
	pos.z = zpos;
	vec3 m = pos + n;
	vec3 d = m + h*(((2.0f*x)/(width-1))-1) + v*(((2.0f*y)/(height-1))-1);

	d = d-pos;

	d = normalize(d);
	
	return d;
}



float Eye::getHeight(){return height;}

float Eye::getWidth(){ return width;}