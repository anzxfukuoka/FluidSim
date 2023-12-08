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

Fluid::Fluid(int count)
{
    vertices = buildCircle(0.6f, count);
}

void Fluid::updateSimulation()
{
    float gravityAcceleration = -9.81f;

    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].y += gravityAcceleration * 0.0001f;
        
    }
}
