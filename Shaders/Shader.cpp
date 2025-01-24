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
