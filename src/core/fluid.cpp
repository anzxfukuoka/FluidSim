#include "fluid.h"

glm::vec3 randomVec3()
{
    float x = (float(rand()) / float((RAND_MAX)) - 0.5f) * 2;
    float y = (float(rand()) / float((RAND_MAX)) - 0.5f) * 2;
    float z = (float(rand()) / float((RAND_MAX)) - 0.5f) * 2;
    return glm::vec3(x, y, z);
}

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

    /*for (int i = 0; i < triangleCount; i++)
    {
        ver.push_back(temp[0]);
        ver.push_back(temp[i + 1]);
        ver.push_back(temp[i + 2]);
    }*/

    return temp;
}

std::vector<glm::vec3> buildRandomField(int vCount)
{
    std::vector<glm::vec3> randomField;

    for (int i = 0; i < vCount; i++)
    {
        randomField.push_back(randomVec3());
    }

    return randomField;
}

std::vector<glm::vec3> buildSquareGrid(int vCount, float spacing)
{
    std::vector<glm::vec3> grid;
    glm::vec3 center = glm::vec3(sqrt(vCount) * spacing / 2, sqrt(vCount) * spacing / 2, 1.0f);

    for (int i = 0; i <= sqrt(vCount); i++)
    {
        for (int j = 0; j <= sqrt(vCount); j++)
        {
            
            grid.push_back(glm::vec3(i* spacing, j* spacing, 1.0f) - center);
        }
    }

    return grid;
}

float smoothingKernerl(float radius, float distance)
{
    if (distance >= radius) 
        return 0;

    float volume = (M_PI * pow(radius, 4.0f)) / 6.0f;
    float val = (radius - distance) * (radius - distance) / volume;
    return val;
}

float smoothingKernerlDerivative(float radius, float distance)
{
    if (distance >= radius)
        return 0;

    float scale = 12.0f / (pow(radius, 4.0f) * M_PI);
    return (distance - radius) * scale;
}



float Fluid::calcDensity(int vertIndex)
{
    float density = 0.0f;
    float threshold = 0.0001f;

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertIndex == i) 
        {
            continue;
        }

        auto vert = vertices[vertIndex];
        auto otherVert = vertices[i];

        float distance = glm::length(vert - otherVert);
        float influance = smoothingKernerl(smothingRadius, distance);
        density += mass * influance;
    }

    return density > threshold ? density : 0.0f;
}

glm::vec3 Fluid::calcGradientPressure(int vertIndex)
{
    glm::vec3 grad = glm::vec3(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertIndex == i) 
        {
            continue;
        }

        glm::vec3 vec = vertices[i] - vertices[vertIndex];
        float dist = glm::length(vec);
        glm::vec3 dir = glm::normalize(vec);

        if (dist == 0)
        {
            dir = randomVec3();
        }
        
        float slope = smoothingKernerlDerivative(smothingRadius, dist);
        float density = densities[i];

        if (density != 0) 
        {
            grad += -getPressureFromDensity(density) * dir * slope * mass / density;
        }
    }

    return grad;
}

float Fluid::getPressureFromDensity(float density)
{
    float densityError = targetDensity - density;
    float pressure = densityError * pressureMultipier;
    return pressure;
}

void Fluid::generatePoints(int pointsCount)
{
    //vertices = buildCircle(0.6f, pointsCount);
    //vertices = buildRandomField(pointsCount);
    vertices =  buildSquareGrid(pointsCount, 0.2f);

    // 
    for (int i = 0; i < vertices.size(); i++)
    {
        velocities.push_back(glm::vec3(0, 0, 0));
        densities.push_back(0);
        normedDensities.push_back(0);
    }
}

Fluid::Fluid(int pointsCount)
{
    generatePoints(pointsCount);
}

void Fluid::updateSimulation()
{
    float maxDens = 0;

    for (int i = 0; i < vertices.size(); i++)
    {

        velocities[i] += glm::vec3(0, -1, 0) * gravity;
        velocities[i] *= ambienceDumping;

        vertices[i] += velocities[i] * simulationSpeed;

        densities[i] = calcDensity(i);
        maxDens = std::max(densities[i], maxDens);
    }

    //pressure forces
        //------
    for (int i = 0; i < vertices.size(); i++)
    {
        if (densities[i] == 0)
            continue;

        glm::vec3 pressureForce = calcGradientPressure(i);
        glm::vec3 pressureAccel = pressureForce / densities[i];
        velocities[i] += pressureAccel;
    }

    //collisions
    //------
    for (int i = 0; i < vertices.size(); i++)
    {
        if (abs(vertices[i].x) >= 1.0f) 
        {
            //signbit returns false when arg > 0
            vertices[i].x = std::signbit(vertices[i].x) ? -1.0f : 1.0f; 
            velocities[i].x = -velocities[i].x * collisionDumping;
        }
        if (abs(vertices[i].y) >= 1.0f)
        {
            vertices[i].y = std::signbit(vertices[i].y) ? -1.0f : 1.0f;
            velocities[i].y = -velocities[i].y * collisionDumping;
        }
        if (abs(vertices[i].z) >= 1.0f)
        {
            vertices[i].z = std::signbit(vertices[i].z) ? -1.0f : 1.0f;
            velocities[i].z *= -velocities[i].z * collisionDumping;
        }

        
        //debug
        if (i == vertices.size() - 1)
        {

            /*if (vertices[i].y > -1.0f && vertices[i].y < 1.0f)
            {
                vertices[i].y += gravity * 0.0001f;
            }*/

            std::cout << velocities[i].x << " " << densities[i] << std::endl;
        }
    }

    ////norm
    ////(for shaders)
    for (int i = 0; i < densities.size(); i++)
    {
        normedDensities[i] = densities[i] / maxDens;
    }
}


int Fluid::getPointSize(glm::vec2 screenResolution)
{
    float pointSize = std::max(screenResolution.x, screenResolution.y) * smothingRadius;
    return pointSize;
}
