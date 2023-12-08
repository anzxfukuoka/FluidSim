/*
* fluid.h
* fluid simulation implementation
*/
#pragma once

#include <iostream>
#include <glm/vec3.hpp> //
#include <glm/glm.hpp>  //
//#include "shaderprog.hpp"
#include <vector>

std::vector<glm::vec3> buildCircle(float radius, int vCount);

class Fluid 
{
private:

	// simulation vars
	// ----------------
	float gravity = 9.81f;

	// wall colisions dumping
	float collisionDumping = 0.88f;

	float simulationSpeed = 0.000001f;

public:

	// points pos
	std::vector<glm::vec3> vertices;
	// points speed
	std::vector<glm::vec3> velocities;

	void generatePoints(int pointsCount);

	Fluid(int count);

	void updateSimulation();

};

