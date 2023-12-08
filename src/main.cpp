#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include <iostream>

// project inputs
#include "graphics/windowmain.h"
#include "core/fluid.h"

Fluid* water;
Renderer* waterRenderer;

void fupdate() 
{
	//std::cout << "update!" << std::endl;
	water->updateSimulation();
	//waterRenderer->updateVertices(&(water->vertices));
}

int main() {
	
	initWindow(600, 800, ".:Fluids:.", color(0.1f, 0.1f, 0.1f, 1.0f));

	water = new Fluid(16);
	waterRenderer = new Renderer(&(water->vertices));

	int excode = showWindow(waterRenderer, &fupdate);

	return excode;
}

