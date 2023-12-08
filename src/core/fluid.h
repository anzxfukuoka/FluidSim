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

public:

	std::vector<glm::vec3> vertices;

	//void generatePoints();

	Fluid(int count);

	void updateSimulation();

};

