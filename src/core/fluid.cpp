#include "fluid.h"

std::vector<glm::vec3> buildCircle(float radius, int vCount)
{
    std::vector<glm::vec3> ver;

    float angle = 360.0f / vCount;

    int triangleCount = vCount - 2;

    std::vector<glm::vec3> temp;
    // positions
    for (int i = 0; i < vCount; i++)
    {
        float currentAngle = angle * i;
        float x = radius * cos(glm::radians(currentAngle));
        float y = radius * sin(glm::radians(currentAngle));
        float z = 0.0f;

        temp.push_back(glm::vec3(x, y, z));
    }

    for (int i = 0; i < triangleCount; i++)
    {
        ver.push_back(temp[0]);
        ver.push_back(temp[i + 1]);
        ver.push_back(temp[i + 2]);
    }

    return ver;
}

float kernerlSmoother(float radius, float distance)
{
    float volume = (M_PI * pow(radius, 4)) / 2;
    float val = std::max(0.0f, radius - distance) ;
    return pow(val, 3) / volume;
}

float Fluid::calcDensity(int vertIndex)
{
    float density = 0;
    float mass = 1;

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertIndex == i) 
        {
            continue;
        }

        auto vert = vertices[vertIndex];
        auto otherVert = vertices[i];

        float distance = glm::length(vert - otherVert);
        float influance = kernerlSmoother(smothingRadius, distance);
        density += mass * influance;
    }

    return density;
}

void Fluid::generatePoints(int pointsCount)
{
    vertices = buildCircle(0.6f, pointsCount);
    
    for (int i = 0; i < vertices.size(); i++)
    {
        velocities.push_back(glm::vec3(0, 0, 0));
    }
}

Fluid::Fluid(int pointsCount)
{
    generatePoints(pointsCount);
}

void Fluid::updateSimulation()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        

        velocities[i] += glm::vec3(0, -1, 0) * gravity;
        vertices[i] += velocities[i] * simulationSpeed;

        //collisions
        //------
        if (abs(vertices[i].x) > 1.0f) 
        {
            vertices[i].x = -std::signbit(vertices[i].x); //returns false when arg > 0
            velocities[i].x *= -1.0f * collisionDumping;
        }
        if (abs(vertices[i].y) > 1.0f)
        {
            vertices[i].y = -std::signbit(vertices[i].y);
            velocities[i].y *= -1.0f * collisionDumping;
        }
        if (abs(vertices[i].z) >= 1.0f)
        {
            vertices[i].z = -std::signbit(vertices[i].z);
            velocities[i].z *= -1.0f * collisionDumping;
        }

        
        //debug
        if (i == 0)
        {

            /*if (vertices[i].y > -1.0f && vertices[i].y < 1.0f)
            {
                vertices[i].y += gravity * 0.0001f;
            }*/

            std::cout << vertices[i].y << " " << calcDensity(0) << std::endl;
        }
    }
}
