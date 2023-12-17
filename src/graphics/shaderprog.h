#pragma once

#include <string>
#include <vector>

class ShaderProg
{
public:
    ShaderProg();

    ~ShaderProg();

    void attach(const char* fileName, unsigned int shaderType);

    void link();

    void use();

    void setUniforms(std::vector<float> densities);

private:
    unsigned int m_pId;

    std::string readShaderFromFile(const char* fileName);
};
