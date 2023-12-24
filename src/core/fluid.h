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

// points generation functions
//---
glm::vec3 randomVec3();
std::vector<glm::vec3> buildCircle(float radius, int vCount);
std::vector<glm::vec3> buildRandomField(int vCount);
std::vector<glm::vec3> buildSquareGrid(int vCount, float spacing);

//---
float smoothingKernerl(float radius, float distance);
float smoothingKernerlDerivative(float radius, float distance);


class Fluid 
{
private:

	// simulation vars
	// ----------------

	float targetDensity = 10.0f;
	float pressureMultipier = 6.0f;

	float gravity = 9.81f;
	float mass = 1.0f;

	// wall colisions dumping
	float collisionDumping = 0.88f;
	float ambienceDumping = 0.88f;

	float simulationSpeed = 0.00002f;

	/// <summary>
	/// range [0.0f, 1.0f] 
	/// (due to openGL coord space)
	/// </summary>
	float smothingRadius = 0.28f;

	float calcDensity(int vertIndex);
	glm::vec3 calcGradientPressure(int vertIndex);
	float getPressureFromDensity(float density);

public:

	// points pos
	std::vector<glm::vec3> vertices;
	// points speed
	std::vector<glm::vec3> velocities;
	// 
	std::vector<float> densities;
	std::vector<float> normedDensities;

	void generatePoints(int pointsCount);

	Fluid(int count);

	void updateSimulation();

	/// <summary>
	/// returns point size according to smothingRadius and screenResolution
	/// </summary>
	/// <returns></returns>
	int getPointSize(glm::vec2 screenResolution);
};

