#include "Scene.h"
#include <string>
#include <iostream>

using namespace std;


int main()
{
	Scene scene;
	Eye eye;
	eye.initialize();
	scene.initialize();
	scene.read("challenge.txt");
	scene.run();
	return 0;
}