#include <fstream>
#include <iostream>
#include <windows.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"


const int width = 800;
const int height = 600;

int customColorId;

const char* vertexShaderSource =
"#version 330 core                      \n"
"                                       \n"
"layout (location = 0) in vec3 aPos;    \n"
"layout (location = 1) in vec3 aColor;  \n"
"layout (location = 2) in vec2 aTex;    \n"
"                                       \n"
"out vec3 ourColor;                     \n"
"out vec2 texCoord;                     \n"
"                                       \n"
"void main()                            \n"
"{                                      \n"
"    gl_Position = vec4(aPos,1.0);      \n"
"    ourColor = aColor;                 \n"
"    texCoord = aTex;                   \n"
"}                                      \n\0";

const char* fragmentShaderSource =
"#version 330 core                      \n"
"                                       \n"
"out vec4 FragColor;                    \n"
"in vec3 ourColor;                      \n"
"in vec2 texCoord;                      \n"
"uniform sampler2D tex0;                \n"
"void main()                            \n"
"{                                      \n"
"    FragColor = texture(tex0, texCoord);\n"
"};                                     \n\0";


float vertices[] = {
    -0.6f, 0.1f, 0.0f,//A 0
    -0.5f, 0.3f, 0.0f,//B 1
    -0.2f, 0.5f, 0.0f,//C 2
    0.2f, 0.5f, 0.0f, //D 3
    0.5f, 0.3f, 0.0f, //E 4
    0.6f, 0.1f, 0.0f, //F 5
    0.0f, -0.2f, 0.0f,//G 6 //Morro
    -0.5f, 0.6f, 0.0f,//H 7
    0.5f, 0.6f, 0.0f, //I 8
    -0.2f, 0.1f, 0.0f,//J 9
    0.2f, 0.1f, 0.0f, //K 10
    -0.3f, 0.0f, 0.0f,//L 11
    0.3f, 0.0f, 0.0f, //M 12

    -0.11f,0.2f,0.0f, //N 13
    0.11f,0.2f,0.0f, //O 14

    -0.08f,0.1f,0.0f, //P 15
    0.08f,0.1f,0.0f    //Q 16
};
unsigned int indices[] = {
    7,1,2, //ORELLA E
    3,8,4,
    0,1,11, //GALTA
    5,4,12,
    11,6,9,
    6,10,12,

    1,2,9,
    3,4,10,

    1,11,9,
    10,4,12,

    2,3,6,
    2,9,13,
    3,10,14,

    2,9,13,
    9,15,6,

    3,14,10,
    10,16,6
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

    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //GLsizei stride = 8 * sizeof(float);
    // void* offsetColor = (void*)(3 * sizeof(float));
    // void* offsetTexture = (void*)(6 * sizeof(float));

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, stride, offsetColor);
    // glEnableVertexAttribArray(1);
    //
    // glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, stride, offsetTexture);
    // glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Texturas --------------------------------------------------------------------------------------------------------
    int width, height, pixelSize;

    //stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load("Images/Monkey.png", &width, &height, &pixelSize, 0);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    //Com es comporta el suavitzat de entre pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (image)
    {
        if (pixelSize == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        std::cout << "Failed to load image" << std::endl;
    }
 
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0); //Evitem que la imatge es modifiqui

    //UNIFORM
    GLuint texUniform = glGetUniformLocation(shaderProgram, "tex0");
    glUseProgram(shaderProgram);
    glUniform1i(texUniform, 0);
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, textureID);        
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
    return 0;
}
