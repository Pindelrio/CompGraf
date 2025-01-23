#include "Shader.h"
#include "../Helpers/Helper.h"
#include <cstddef>
#include <string>
#include "glad/glad.h"

unsigned int Shader::CreateShaders(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexShaderCode = Helper::ReadTextFile(vertexPath); //Guardem el resultat per no perdrel al assignar el punter a c_str()
    const char* vertexShaderSource = vertexShaderCode.c_str();

    std::string fragmentShaderCode = Helper::ReadTextFile(fragmentPath); //Guardem el resultat per no perdrel al assignar el punter a c_str()
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    
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

    return shaderProgram;
}

void Shader::BindShaders(unsigned int VAO, unsigned int VBO, unsigned int IBO, const float* vertices, const unsigned int* indices)
{
    // unsigned int VAO;
    // unsigned int VBO;
    // unsigned int IBO;
    
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &IBO);
    //
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    GLsizei stride = 8 * sizeof(float);
    void* offsetColor = (void*)(3 * sizeof(float));
    void* offsetTexture = (void*)(6 * sizeof(float));
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, stride, offsetColor);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, stride, offsetTexture);
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
