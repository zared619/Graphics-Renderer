#include "VoxelBuffer.h"

VoxelBuffer::VoxelBuffer()
{
	dimensions.x = 0;
	dimensions.y = 0;
	dimensions.z = 0;
	sizeOfBuffer = 0;
}

VoxelBuffer::VoxelBuffer(float delta, const ivec3& dimensions)
{
	this->delta = delta;
	this->dimensions = dimensions;

	sizeOfBuffer = dimensions.x*dimensions.y*dimensions.z;
	buffer = new voxel[sizeOfBuffer];
}

VoxelBuffer::~VoxelBuffer()
{
	delete buffer;
}

voxel* VoxelBuffer::getVoxel(vec3 vox) const
{
	ivec3 nVox;
	nVox.x = (int)(vox.x/delta);
	nVox.y = (int)(vox.y/delta);
	nVox.z = (int)(vox.z/delta);

	return &buffer[nVox.x + nVox.y*dimensions.x + nVox.z*dimensions.x*dimensions.y];
}

float VoxelBuffer::densityRead(const vec3& coords) const
{
	return getVoxel(coords)->density;
}

float VoxelBuffer::lightRead(const vec3& coords) const
{
	return getVoxel(coords)->light;
}

void VoxelBuffer::densityWrite(const vec3& coords, float value)
{
	getVoxel(coords)->density = value;
}

void VoxelBuffer::lightWrite(const vec3& coords, float value)
{
	getVoxel(coords)->light = value;
}

vec3 VoxelBuffer::getVoxelCenter(const vec3& coords) const
{
	ivec3 nVox;
	nVox.x = (int)(coords.x/delta);
	nVox.y = (int)(coords.y/delta);
	nVox.z = (int)(coords.z/delta);

	return getVoxelCenter(nVox);
}

vec3 VoxelBuffer::getVoxelCenter(const ivec3& coords) const
{
	vec3 ret;
	ret.x = coords.x * delta + (delta/2);
	ret.y = coords.y * delta + (delta/2);
	ret.z = coords.z * delta + (delta/2);
	return ret;
}

VoxelBuffer* VoxelBuffer::factory(float delt, vec3 dim, std::string fname)
{
	float delta = delt;;
	std::fstream fin;
	char garbage[256];
	fin.open(fname);
	ivec3 dimensions;
	dimensions.x = (int)dim.x;
	dimensions.y = (int)dim.y;
	dimensions.z = (int)dim.z;
	

	VoxelBuffer* vox = new VoxelBuffer(delta,dimensions);
	//Ignore the first 13 lines of the file
	for(int i = 0; i<=13; i++)
		fin.getline(garbage, 256);

	for(int i = 0; i<=vox->sizeOfBuffer; i++)
	{
		fin>> vox->buffer[i].density;
	}

	fin.close();

	return vox;
}

