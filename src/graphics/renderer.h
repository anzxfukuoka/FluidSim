﻿#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> //
#include <glm/glm.hpp>  //
//#include "shaderprog.hpp"
#include <vector>
using namespace std;

void buildCircle(float radius, int vCount);

void initRenderBuffers();

void renderFluid();