#pragma once
#include "glad/glad.h"
#include "glm/fwd.hpp"

class Lights
{
public:
    static void CreateSpotLight(GLuint shaderProgram);
    static void CreatePointLight(unsigned int shaderProgram, const glm::vec3 &pointLightColor);
    static void DynamicColorSpotLight(GLuint shaderProgram);
};
