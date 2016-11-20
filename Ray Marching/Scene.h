#ifndef Scene_h
#define Scene_h


#include "VoxelBuffer.h";
#include "vec3.h"
#include "EasyBMP.h"
#include "Eye.h"
#include <string>
#include <fstream>
#include "ray.h"
using std::string;

class Scene
{
private:
	float delt, step, fovy, trans, deltaTrans, kappa;
	vec3 xyzc, brgb, mrgb, eyep, vdir,uvec, lpos, lcol, color, n, curRayPos;
	float resX, resY;
	string filename, file;
	VoxelBuffer* subject1;
	Eye eye;
public:
	void initialize();
	void run();
	void read(string fname);
	void setColor();
	void march(vec3 n, vec3 curPos);
	bool isLegal(vec3 pos);
	float getLight(vec3 a);

};

#endif