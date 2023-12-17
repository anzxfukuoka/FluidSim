/*
* renderer.h
* rendering stuff..
*/
#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> //
#include <glm/glm.hpp>  //

#include "shaderprog.h"

#include "../core/fluid.h"

using namespace std;

/// <summary>
/// fluid renderer
/// </summary>
class FluidRenderer
{
private:

	// screen resolution
	glm::vec2 resolution;

	// fluid to render
	Fluid* fluid;

	// object id variables
	unsigned int vertexBuffer;
	unsigned int vertexArray;
	
	// shader
	ShaderProg shaderProg;

public:

	FluidRenderer(Fluid* fluid, glm::vec2 resolution);

	void initShader();
	//void updateVertices(std::vector<glm::vec3> *vertices);
	void initRenderBuffers();
	void render();
};