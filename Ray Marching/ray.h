/********************************
* Zared Hollabaugh				*
* February 13 2015 GCC COMP 361 *
* 								*
********************************/
#pragma once

#include "vec3.h"

struct ray
{
	ray(vec3 pos, vec3 dir);

	vec3 operator() (float p);

	vec3 pos, direction;
};