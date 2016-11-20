 #include "Scene.h"

void Scene::initialize()
{
	delt = 0; 
	step = 0; 
	fovy = 0; 
	trans = 0; 
	deltaTrans = 0;
	kappa  = 0; 
	resX = 0; 
	resY = 0;

	xyzc(0);
	brgb(0);
	mrgb(0);
	eyep(0);
	vdir(0);
	uvec(0);
	lpos(0);
	lcol(0);
	color(0);
	n(0);
	curRayPos(0);
}

void Scene::run()
{
	subject1 = VoxelBuffer::factory(delt,xyzc,file);

	setColor();
}

void Scene::read(string fname)
{
	std::fstream fin;
	file = fname;
	string temp;
	fin.open(fname);
	if(fin.fail())
	{
		std::cout<<"Could not open input file"<<std::endl;
		exit(1);
	}
	fin >> temp;
	fin >> delt;

	fin >> temp;
	fin >> step;

	fin >> temp;
	fin >> xyzc.x;
	fin >> xyzc.y;
	fin >> xyzc.z;

	fin >> temp;
	fin >> brgb.x;
	fin >> brgb.y;
	fin >> brgb.z;

	fin >> temp;
	fin >> mrgb.x;
	fin >> mrgb.y;
	fin >> mrgb.z;

	fin >> temp;
	fin >> filename;

	fin >> temp;
	fin >> resX;
	fin >> resY;

	fin >> temp;
	fin >> eyep.x;
	fin >> eyep.y;
	fin >> eyep.z;

	fin >> temp;
	fin >> vdir.x;
	fin >> vdir.y;
	fin >> vdir.z;

	fin >> temp;
	fin >> uvec.x;
	fin >> uvec.y;
	fin >> uvec.z;

	fin >> temp;
	fin >> fovy;

	fin >> temp;
	fin >> lpos.x;
	fin >> lpos.y;
	fin >> lpos.z;

	fin >> temp;
	fin >> lcol.x;
	fin >> lcol.y;
	fin >> lcol.z;

	eye.setFoV(fovy);
	eye.setHeight(resY);
	eye.setUVec(uvec);
	eye.setVDir(vdir);
	eye.setWidth(resX);
	eye.setX(xyzc.x);
	eye.setY(xyzc.y);
	eye.setZ(xyzc.z);

	fin.close();
}

void Scene::setColor()
{
	kappa = 0.8f;
	BMP output;
	output.SetSize((int)resX, (int)resY);
	output.SetBitDepth(24);
	for(int i = 0; i<resX-1; i++)
	{
		for(int j = 0; j<resY-1; j++)
		{
			n = eye.generate((float)i, resY-(float)j);
			curRayPos = eyep;
			march(n, curRayPos);
 			color =color*255;

			output(i, j)->Red = (ebmpBYTE)abs(color.x);
			output(i, j)->Green = (ebmpBYTE)abs(color.y);
			output(i, j)->Blue = (ebmpBYTE)abs(color.z);
		}
	}

	const char * c = filename.c_str();

	output.WriteToFile(c);
}

void Scene::march(vec3 n, vec3 curPos)
{
	bool legal = false;
	bool holder = true;
	double density =0;
	float maxStep = (1/step)*(curPos.z+xyzc.z);
	color.x = 0;
	color.y = 0;
	color.z = 0;
	trans = 1;
	for(int i = 0; i < maxStep; i++)
	{
		curPos = curPos+(n*step);
		legal = isLegal(curPos);
		if(!legal)
			continue;
		if(trans > 0.000001)
		{
			density = subject1->densityRead(curPos);
			deltaTrans = (float)exp(-kappa*step*density);
			trans *= deltaTrans;
			//color = color + (mrgb*((1-deltaTrans)/kappa)*trans);
			color = color + (mrgb *lcol)*((1-deltaTrans)/kappa)*trans*getLight(curPos);	
		}
	}

	//Set background color
	color = color + brgb * trans;
	

	if(color.x >= 1 )
		color.x = 1;
	else if(color.y >=1)
		color.y = 1;
	else if(color.z >= 1)
		color.z = 1;

	if(color.x < 0)
		color.x = 0;
	else if(color.y < 0)
		color.y = 0;
	else if(color.z < 0)
		color.z = 0;
}

bool Scene::isLegal(vec3 pos)
{
	bool temp; 

	//Returns false if any position coordinate is outside of the voxel buffer
	if(pos.x > (xyzc.x*delt-1) || pos.y > (xyzc.y*delt-1) || pos.z > (xyzc.z*delt-1)|| pos.x < 0 || pos.y < 0 || pos.z < 0)
		return false;
	else 
		return true;

	return temp;
}

float Scene::getLight(vec3 a)
{
	float num = subject1->lightRead(a);

	if(num<0)
	{
		vec3 voxLoc = subject1->getVoxelCenter(a);
		ray towardsLight(voxLoc, (lpos-voxLoc));

		float sum = 0;
		float posOnRay = step;
		vec3 curLoc = towardsLight(posOnRay);
		float iter = towardsLight.direction.magnitude();
		towardsLight.direction = towardsLight.direction.normalize();

		for(double i = 0; i<iter; i+=step)
		{
			if(isLegal(curLoc))
			{
				sum += subject1->densityRead(curLoc)*step;
				posOnRay += step;
				curLoc = towardsLight(posOnRay);
			}
		}

		num = exp(-kappa*sum);
		subject1->lightWrite(voxLoc, num);
		return num;
	}
	else
		return num;

}