#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


const int width = 800;
const int height = 600;

int customColorId;

const char* vertexShaderSource =
"#version 330 core\n"
"\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos,1.0);\n"
"    ourColor = aColor;\n"
"}\n\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"\n"
"void main()\n"
"{\n"
"    FragColor = vec4(ourColor, 1.0f);\n"
"};\n\0";

std::string ReadTextFile(const std::string& fileName);

float vertices[] = {
     0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   
    -0.5f,-0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
     0.5f,-0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Grafica", nullptr, nullptr);

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

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    customColorId = glGetUniformLocation(shaderProgram, "alternativeColor");
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    float stride = 6 * sizeof(float);
    void* offset = (void*)(3 * sizeof(float));

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
        //glUniform4f(customColorId, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        glfwSwapBuffers(window);
        glfwPollEvents();

        Sleep(500);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
    return 0;
}

std::string ReadTextFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) return "";
    
    std::stringstream stringbuffer;
    stringbuffer << file.rdbuf();
    file.close();
    return stringbuffer.str();
}