#include "renderer.h"

//std::vector<glm::vec3> vertices; //


FluidRenderer::FluidRenderer(Fluid* fluid, glm::vec2 resolution)
    : fluid(fluid), resolution(resolution)
{
    initShader();
}

void FluidRenderer::initShader()
{
    
    // attachment of shaders to program object
    shaderProg.attach("resources/default_vert.glsl", GL_VERTEX_SHADER);
    shaderProg.attach("resources/default_frag.glsl", GL_FRAGMENT_SHADER);
    shaderProg.link();
}

void FluidRenderer::initRenderBuffers()
{
    // buffer
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
}

void FluidRenderer::render()
{
    // send points to gpu
    // ------
    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * fluid->vertices.size(), &(*vertices)[0], GL_STATIC_DRAW); // asd
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * fluid->vertices.size(), &((*fluid).vertices)[0], GL_STATIC_DRAW); // asd

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // apply shader
    // ------

    shaderProg.use();
    shaderProg.setUniforms();

    // verteces draw
    // ------

    glBindVertexArray(vertexArray);

    //glPointSize(100);
    glPointSize(fluid->getPointSize(resolution));

    glDrawArrays(GL_POINTS, 0, fluid->vertices.size());
}
