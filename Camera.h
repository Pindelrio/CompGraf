#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/vector_angle.hpp"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    int width, height;

    float speed = 0.1f;

    Camera(int width, int height, glm::vec3 positionCamera);
    void CameraMatrix(float FOV, float nearPlane, float farPlane, unsigned int shaderProgramId, const char* uniform);
    void CameraInput(GLFWwindow* window);
};
