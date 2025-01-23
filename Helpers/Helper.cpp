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


