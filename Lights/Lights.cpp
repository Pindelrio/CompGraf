#include "Lights.h"


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

void Lights::CreateSpotLight(GLuint shaderProgram)
{
    // Configura spotlight
    glUseProgram(shaderProgram);

    // Spotlight position
    GLint spotlightPosLoc = glGetUniformLocation(shaderProgram, "spotlightPosition");
    glUniform3f(spotlightPosLoc, 0.0f, 2.0f, 2.0f);

    // Spotlight direction
    GLint spotlightDirLoc = glGetUniformLocation(shaderProgram, "spotlightDirection");
    glUniform3f(spotlightDirLoc, 0.0f, -1.0f, -1.0f);

    // Spotlight cutoff angles
    GLint spotlightCutoffLoc = glGetUniformLocation(shaderProgram, "spotlightCutoff");
    glUniform1f(spotlightCutoffLoc, glm::cos(glm::radians(12.5f)));

    GLint spotlightOuterCutoffLoc = glGetUniformLocation(shaderProgram, "spotlightOuterCutoff");
    glUniform1f(spotlightOuterCutoffLoc, glm::cos(glm::radians(17.5f)));

    // Spotlight attenuation
    GLint spotlightAttenuationLoc = glGetUniformLocation(shaderProgram, "spotlightAttenuation");
    glUniform1f(spotlightAttenuationLoc, 0.09f);

}

void Lights::CreatePointLight(GLuint shaderProgram, const glm::vec3 &pointLightColor)
{
    // Configurar la Point Light
    glm::vec3 pointLightPosition(2.0f, 1.5f, 1.0f); // Posició
    
    float pointLightAttenuation = 0.1f;             // Atenuació

    // Passar els valors al shader
    glUniform3fv(glGetUniformLocation(shaderProgram, "pointLightPosition"), 1, glm::value_ptr(pointLightPosition));
    glUniform3fv(glGetUniformLocation(shaderProgram, "pointLightColor"), 1, glm::value_ptr(pointLightColor));
    glUniform1f(glGetUniformLocation(shaderProgram, "pointLightAttenuation"), pointLightAttenuation);
}

void Lights::DynamicColorSpotLight(GLuint shaderProgram)
{
    float time = glfwGetTime(); 
    float intensity = (sin(time) + 1.0f) / 2.0f; // Oscil·la entre 0 i 1
    glm::vec4 spotlightColor(0.2f, intensity, 0.2f, 1.0f);
    glUniform4fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(spotlightColor));
}
