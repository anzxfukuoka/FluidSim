#include "renderer.h"

//std::vector<glm::vec3> vertices; //


Renderer::Renderer(std::vector<glm::vec3> vertices) : vertices(vertices)
{

}

void Renderer::initRenderBuffers()
{
    // buffer
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);


    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // asd

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
}

void Renderer::render()
{
    //myProgram.use();

    glBindVertexArray(vertexArray);

    glPointSize(20);

    glDrawArrays(GL_POINTS, 0, vertices.size());
}
