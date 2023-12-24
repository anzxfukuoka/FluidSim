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

	float targetDensity = 1.01f;
	float pressureMultipier = 0.2f;

	bool enableGravity = 0;
	float gravity = 9.81f;
	float mass = 0.11f;

	// wall colisions dumping
	float collisionDumping = 0.88f;
	float ambienceDumping = 0.88f;

	float simulationSpeed = 0.0002f;

	/// <summary>
	/// range [0.0f, 1.0f] 
	/// (due to openGL coord space)
	/// </summary>
	float smothingRadius = 0.08f;

	float cursorRadius = 0.2f;
	float cursorForce = 100.0f;

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

	void updateSimulation(float cursorX, float cursorY);

	/// <summary>
	/// returns point size according to smothingRadius and screenResolution
	/// </summary>
	/// <returns></returns>
	int getPointSize(glm::vec2 screenResolution);
};

