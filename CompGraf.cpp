#include <fstream>
#include <iostream>
#include <windows.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Lights/Lights.h"
#include "Shaders/Shader.h"
#include "Shapes/Cube.h"
#include "Shapes/Sphere.h"
#include "Shapes/Triangle.h"


const int width = 1024;
const int height = 720;

const char* vertexPath = "Shaders/vertex.glsl";
const char* fragmentPath = "Shaders/fragment.glsl";

int customColorId;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Computacio Grafica", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int shaderProgram = Shader::CreateShaders(vertexPath,fragmentPath);

    // LIGHTS
    Lights::CreateSpotLight(shaderProgram);
    glm::vec3 pointLightColor(1.0f,1.0f,1.0f);
    Lights::CreatePointLight(shaderProgram, pointLightColor);
    //-------------------------------

    GLuint textureID;
    //--- Objecte 1
    Texture::Texture("Images/Monkey.png", shaderProgram, false, textureID);
    Mesh cubMesh(Cube::vertices, sizeof(Cube::vertices) / sizeof(Cube::vertices[0]),
              Cube::indices, sizeof(Cube::indices) / sizeof(Cube::indices[0]), 
              textureID);

    //--- Objecte 2
    Texture::Texture("Images/Brick_Texture.jpg", shaderProgram, true, textureID);
    Mesh triangleMesh(Triangle::vertices, sizeof(Triangle::vertices) / sizeof(Triangle::vertices[0]),
              Triangle::indices, sizeof(Triangle::indices) / sizeof(Triangle::indices[0]), 
              textureID);

    //--- Objecte 3
    Texture::Texture("Images/Image.jpg", shaderProgram, false, textureID);
    Mesh cub2Mesh(Cube::vertices, sizeof(Cube::vertices) / sizeof(Cube::vertices[0]),
              Cube::indices, sizeof(Cube::indices) / sizeof(Cube::indices[0]), 
              textureID);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Camera ourCamera(width,height,glm::vec3(0.0f,0.0f,2.0f));
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourCamera.CameraMatrix(45.f,0.1f,100.0f, shaderProgram, "cameraMatrix");
        ourCamera.CameraInput(window);

        //Dynamic Spot lights
        Lights::DynamicColorSpotLight(shaderProgram);
        

        // Transformació per al primer mesh (centrat)
        glm::mat4 model1 = glm::mat4(1.0f); // Identitat
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model1));
        triangleMesh.Draw(shaderProgram);

        // Transformació per al segon mesh (dalt a la dreta)
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(0.75f, 0.75f, 0.0f)); // Moure a la cantonada superior dreta
        model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));       // Escalar si cal per ajustar-lo
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        cubMesh.Draw(shaderProgram);

    
        // Transformació per al tercer mesh (baix a la esq)
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(-0.75f, -0.75f, 0.0f)); 
        model3 = glm::scale(model3, glm::vec3(0.6f, 0.6f, 0.6f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model3));
        cub2Mesh.Draw(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
