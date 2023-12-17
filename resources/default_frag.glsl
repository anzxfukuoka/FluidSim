#version 330 core
out vec4 fragColor;

in vec4 myVarOut;

const float PI = 3.1415926535897932384626433832795;
in float densitiy;

void main()  
{
    float disToCenter = distance(gl_PointCoord, vec2(0.5f, 0.5f));  
    float transparancy = 1 - sin(sqrt(disToCenter * PI)); // sin(sqrt(gl_PointCoord.x * gl_PointCoord.x + gl_PointCoord.y * gl_PointCoord.y) * PI);// + sin(gl_PointCoord.y * PI);
    transparancy = min(pow(transparancy, 2), 0.28f);

    fragColor = vec4(0.1f, 1.0f, densitiy, transparancy * 2); //* vec4(gl_PointCoord.x, gl_PointCoord.y, 0.0f, 1.0f); //  myVarOut * ;
};