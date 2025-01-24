#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 texCoord;
out vec3 norm; // Normal interpolada

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 cameraMatrix;
          
void main()
{                          
    gl_Position = cameraMatrix * model * vec4(aPos,1.0);
    ourColor = aColor;
    texCoord = aTex; 
    norm = mat3(transpose(inverse(model))) * aNormal; // Transformar normals correctament
        
}