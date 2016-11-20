/********************************
* Zared Hollabaugh				*
* February 13 2015 GCC COMP 361 *
* 								*
********************************/

#pragma once

#include "vec3.h"
#include <math.h>

class Eye
{
private:
	float xpos, ypos, zpos, fovy, height, width;
	
public:
	vec3 vdir, uvec;
	void setX(float pos);
	void setY(float pos);
	void setZ(float pos);
	void initialize();
	void setHeight(float h);
	void setWidth(float h);
	void setFoV(float y);
	void setVDir(vec3 vec);
	void setUVec(vec3 vec);
	float getHeight();
	float getWidth();
	float magnitude(vec3 a);
	vec3 generate(float x, float y);
	vec3 normalize(vec3 a);
};