#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> //
#include <glm/glm.hpp>  //
//#include "shaderprog.hpp"
#include <vector>

using namespace std;

class Renderer
{
private:

	std::vector<glm::vec3> *vertices; 

	// object id variables
	unsigned int vertexBuffer;
	unsigned int vertexArray;

public:

	Renderer(std::vector<glm::vec3> *vertices);

	void updateVertices(std::vector<glm::vec3> *vertices);
	void initRenderBuffers();
	void render();
};