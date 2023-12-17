#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in float inDensitiy;

uniform vec4 myVar = {0.5, 0.2, 0.7, 1.0};
uniform float densities[];

out vec4 myVarOut;

out float densitiy;

void main()  
{
    gl_Position = vec4(inPosition, 1.0);
    //gl_Position = vec4(gl_VertexID * 0.1, 0.0, 0.0, 1.0);
    
    myVarOut = myVar;
    
    int id = 0 * gl_VertexID;
    densitiy = inDensitiy;
};