#version 330 core
layout (location = 0) in vec3 inPosition;

uniform vec4 myVar = {0.5, 0.2, 0.7, 1.0};
out vec4 myVarOut;

void main()  
{
    gl_Position = vec4(inPosition, 1.0);
    myVarOut = myVar;
};