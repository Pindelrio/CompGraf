#pragma once

class Shader
{
public:
    static unsigned int CreateShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    static void BindShaders(unsigned int VAO, unsigned int VBO, unsigned int IBO, const float* vertices, const unsigned int* indices);
};
