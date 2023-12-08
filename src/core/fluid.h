/*
* fluid.h
* fluid simulation implementation
*/
#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>    // std::max

#include <glm/vec3.hpp> //
#include <glm/glm.hpp>  //
//#include "shaderprog.hpp"

//---
std::vector<glm::vec3> buildCircle(float radius, int vCount);

//---
float kernerlSmoother(float radius, float distance);



class Fluid 
{
private:

	// simulation vars
	// ----------------
	float gravity = 9.81f;

	// wall colisions dumping
	float collisionDumping = 0.88f;

	float simulationSpeed = 0.000001f;

	float smothingRadius = 1.0f;

	float calcDensity(int vertIndex);

public:

	// points pos
	std::vector<glm::vec3> vertices;
	// points speed
	std::vector<glm::vec3> velocities;

	void generatePoints(int pointsCount);

	Fluid(int count);

	void updateSimulation();

};

