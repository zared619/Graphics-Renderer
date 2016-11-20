/********************************
* Zared Hollabaugh				*
* February 13 2015 GCC COMP 361 *
* 								*
********************************/

#include "ray.h"

ray::ray(vec3 p, vec3 dir)
{
	pos = p;
	direction = dir;
	direction = direction.normalize();
}

vec3 ray::operator() (float p)
{
	return pos + direction*p;
}