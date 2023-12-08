#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include <iostream>

// project inputs
#include "graphics/windowmain.h"
#include "core/fluid.h"

Fluid* water;

void fupdate() 
{
	std::cout << "update!" << std::endl;
	water->updateSimulation();
}

int main() {
	
	initWindow(600, 800, ".:Fluids:.");

	water = new Fluid(128);
	//Renderer* renderer = new Renderer(buildCircle(0.6f, 6));
	Renderer* renderer = new Renderer(water->vertices);

	int excode = showWindow(renderer, &fupdate);

	return excode;
}

