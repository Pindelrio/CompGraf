#pragma once
#include "glad/glad.h"

class Texture
{
public:
    Texture(char const* path, unsigned int shaderProgram , bool flip, GLuint &outTextureID);
    
};
