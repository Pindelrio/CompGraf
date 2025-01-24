#version 330 core

out vec4 FragColor;

in vec3 fragPos; // Posició del fragment
in vec3 norm; // Normal interpolada
in vec2 texCoord; // Coordenades de textura

uniform sampler2D tex0; // Textura
uniform vec4 lightColor; // Color de la llum del spotlight
uniform vec3 objectColor; // Color base de l'objecte

// Spotlight properties
uniform vec3 spotlightPosition; // Posició del spotlight
uniform vec3 spotlightDirection; // Direcció del spotlight
uniform float spotlightCutoff; // Angle de tall (cosinus de l'angle)
uniform float spotlightOuterCutoff; // Angle extern
uniform float spotlightAttenuation; // Atenuació

// Point Light properties
uniform vec3 pointLightPosition; // Posició de la llum puntual
uniform vec3 pointLightColor; // Color de la llum puntual
uniform float pointLightAttenuation; // Atenuació de la llum puntual

void main()
{
    // --- Spotlight ---
    vec3 lightDirSpot = normalize(spotlightPosition - fragPos);
    float theta = dot(lightDirSpot, normalize(-spotlightDirection));
    float epsilon = spotlightCutoff - spotlightOuterCutoff;
    float intensitySpot = clamp((theta - spotlightOuterCutoff) / epsilon, 0.0, 1.0);

    float distanceSpot = length(spotlightPosition - fragPos);
    float attenuationSpot = 1.0 / (1.0 + spotlightAttenuation * distanceSpot * distanceSpot);

    vec3 normDir = normalize(norm);
    vec3 diffuseSpot = max(dot(normDir, lightDirSpot), 0.0) * lightColor.rgb * attenuationSpot * intensitySpot;
    vec3 ambientSpot = 0.1 * lightColor.rgb;

    // --- Point Light ---
    vec3 lightDirPoint = normalize(pointLightPosition - fragPos);
    float distancePoint = length(pointLightPosition - fragPos);
    float attenuationPoint = 1.0 / (1.0 + pointLightAttenuation * distancePoint * distancePoint);

    vec3 diffusePoint = max(dot(normDir, lightDirPoint), 0.0) * pointLightColor * attenuationPoint;
    vec3 ambientPoint = 0.1 * pointLightColor;

    // --- Combine Lighting ---
    vec3 totalLighting = (ambientSpot + diffuseSpot) + (ambientPoint + diffusePoint);

    // Combinar textura amb il·luminació
    vec4 texColor = texture(tex0, texCoord);
    FragColor = vec4(totalLighting * texColor.rgb, texColor.a);
}

/*#version 330 core

out vec4 FragColor;

in vec3 fragPos; // Posició del fragment
in vec3 norm; // Normal interpolada
in vec2 texCoord; // Coordenades de textura

uniform sampler2D tex0; // Textura
uniform vec4 lightColor; // Color de la llum
uniform vec3 objectColor; // Color base de l'objecte

// Spotlight properties
uniform vec3 spotlightPosition; // Posició del spotlight
uniform vec3 spotlightDirection; // Direcció del spotlight
uniform float spotlightCutoff; // Angle de tall (cosinus de l'angle)
uniform float spotlightOuterCutoff; // Angle extern
uniform float spotlightAttenuation; // Atenuació

void main()
{
    // Vector entre la llum i el punt
    vec3 lightDir = normalize(spotlightPosition - fragPos);

    // Angle entre el vector de llum i la direcció del spotlight
    float theta = dot(lightDir, normalize(-spotlightDirection));

    // Aplica atenuació segons l'angle de tall
    float epsilon = spotlightCutoff - spotlightOuterCutoff;
    float intensity = clamp((theta - spotlightOuterCutoff) / epsilon, 0.0, 1.0);

    // Atenuació de la llum
    float distance = length(spotlightPosition - fragPos);
    float attenuation = 1.0 / (1.0 + spotlightAttenuation * distance * distance);

    // Calcula el color final
    vec3 normDir = normalize(norm); // Normalitzar la normal
    vec3 diffuse = max(dot(normDir, lightDir), 0.0) * lightColor.rgb * attenuation * intensity;
    vec3 ambient = 0.1 * lightColor.rgb; // Llum ambiental mínima
    vec3 lighting = ambient + diffuse;

    // Combinar textura amb il·luminació
    vec4 texColor = texture(tex0, texCoord);
    FragColor = vec4(lighting * texColor.rgb, texColor.a);

}*/
