#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 positionCamera)
{
    Camera::width = width;
    Camera::height = height;
    position = positionCamera;
}

void Camera::CameraMatrix(float FOV, float nearPlane, float farPlane, unsigned int shaderProgramId, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    projection = glm::perspective(FOV,(float)width/(float)height,nearPlane,farPlane);

    GLint cameraUniform = glGetUniformLocation(shaderProgramId, uniform);
    glUniformMatrix4fv(cameraUniform, 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::CameraInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W)) { position += speed + orientation;}
    if (glfwGetKey(window, GLFW_KEY_D)) { position += speed * -glm::normalize(glm::cross(orientation,up));}
    if (glfwGetKey(window, GLFW_KEY_S)) { position += speed - orientation; }
    if (glfwGetKey(window, GLFW_KEY_A)) { position += speed * glm::normalize(glm::cross(orientation,up)); }

    if (glfwGetKey(window, GLFW_KEY_Q)) { position += speed * up; }
    if (glfwGetKey(window, GLFW_KEY_E)) { position += speed * -up; }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) { speed = 0.1f; }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) { speed = 1.f; }

    //Posicio inicial
    if (glfwGetKey(window, GLFW_KEY_F)) { position = glm::vec3(0.0f,0.0f,2.0f); }
    
}
