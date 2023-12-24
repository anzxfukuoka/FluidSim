#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include <iostream>

// project inputs
#include "graphics/windowmain.h"
#include "core/fluid.h"

Fluid* water;
FluidRenderer* waterRenderer;

const float WIDTH = 1000;
const float HEIGHT = 800;

void fupdate() 
{
	auto mousePos = getMousePosition();
	water->updateSimulation(mousePos.x, mousePos.y);
	//waterRenderer->updateVertices(&(water->vertices));
}

int main() {
	
	initWindow(WIDTH, HEIGHT, ".:Fluids:.", color(0.1f, 0.1f, 0.1f, 1.0f));

	printf("%s\n", glGetString(GL_VERSION));

	water = new Fluid(600);
	waterRenderer = new FluidRenderer(water, glm::vec2(WIDTH, HEIGHT));

	int excode = showWindow(waterRenderer, &fupdate, 1);

	return excode;
}

