#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include <iostream>

// project inputs
#include "graphics/windowmain.h"

int main() {
	
	initWindow(600, 800, ".:Fluids:.");

	int excode = showWindow();

	return excode;
}

