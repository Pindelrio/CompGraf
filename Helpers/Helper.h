#pragma once
#include <string>

#include "glad/glad.h"

class Helper
{
public:
    static std::string ReadTextFile(const std::string& path);
    static GLint LoadTexture(char const* path, bool flip = false, unsigned int shaderProgram =0);
};
