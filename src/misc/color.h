#pragma once

#include <GLFW/glfw3.h>

struct color 
{
	GLfloat r = 1.0f;
	GLfloat g = 1.0f;
	GLfloat b = 1.0f;
	GLfloat a = 1.0f;

	color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) 
		: r(r), g(g), b(b), a(a) 
	{}
};