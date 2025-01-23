#pragma once
#include <vector>

#include "glad/glad.h"

class Mesh
{
public:
    GLuint VAO, VBO, IBO;
    GLuint textureID;
    size_t indexSize;
    
    Mesh(const float* vertices, size_t vertexCount, 
         const unsigned int* indices, size_t indexCount, GLuint textureID);
        
    void Draw(GLuint shaderProgram);
    ~Mesh();
    
};
