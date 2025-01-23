#include "Helper.h"
#include <fstream>
#include <sstream>

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
