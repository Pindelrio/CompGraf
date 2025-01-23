#include "Helper.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"
#include "stb/stb_image.h"

std::string Helper::ReadTextFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return ""; 

    std::stringstream buffer{};
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

GLint Helper::LoadTexture(char const* path, bool flip, unsigned int shaderProgram)
{
    // Texturas --------------------------------------------------------------------------------------------------------
    int width, height, pixelSize;

    stbi_set_flip_vertically_on_load(flip);
    unsigned char* image = stbi_load(path, &width, &height, &pixelSize, 0);

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
    glEnable(GL_DEPTH_TEST);
    
    return textureID;
}

