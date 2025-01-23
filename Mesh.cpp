#include "Mesh.h"
#include "glad/glad.h"

Mesh::Mesh(const float* vertices, size_t vertexCount, const unsigned int* indices, size_t indexCount, GLuint textureID): textureID(textureID)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    
    GLsizei stride = 8 * sizeof(float);
    void* offsetColor = (void*)(3 * sizeof(float));
    void* offsetTexture = (void*)(6 * sizeof(float));
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, stride, offsetColor);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, stride, offsetTexture);
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    indexSize = indexCount;
}

void Mesh::Draw(GLuint shaderProgram)
{
    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
