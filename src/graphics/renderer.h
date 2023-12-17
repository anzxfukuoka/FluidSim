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

using namespace std;

class Renderer
{
private:

	std::vector<glm::vec3> *vertices; 

	// object id variables
	unsigned int vertexBuffer;
	unsigned int vertexArray;
	
	// shader
	ShaderProg shaderProg;

	int pointSize;

public:

	Renderer(std::vector<glm::vec3> *vertices, int pointSize);

	void initShader();
	//void updateVertices(std::vector<glm::vec3> *vertices);
	void initRenderBuffers();
	void render();
};