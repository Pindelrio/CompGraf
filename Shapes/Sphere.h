
# define M_PI          3.141592653589793238462643383279502884L /* pi */
#include <vector>
#include <cmath>

struct Vertex {
    float x, y, z; // Posició
    float nx, ny, nz; // Normals
    float u, v; // Coordenades de textura
};

class Sphere
{
public:
    Sphere(float radius, int stacks, int slices) {
        generateSphere(radius, stacks, slices);
    }

    const float* getVertices() const {
    
        return reinterpret_cast<const float*>(vertices.data());
    }

    const unsigned int* getIndices() const {
        return indices.data();
    }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void generateSphere(float radius, int stacks, int slices) {
        for (int i = 0; i <= stacks; ++i) {
            float stackAngle = M_PI / 2 - i * (M_PI / stacks); // Angle per a cada stack
            float xy = radius * cos(stackAngle);              // Coordenada XY
            float z = radius * sin(stackAngle);               // Coordenada Z

            for (int j = 0; j <= slices; ++j) {
                float sliceAngle = j * (2 * M_PI / slices);   // Angle per a cada slice

                // Coordenades cartesianes
                float x = xy * cos(sliceAngle);
                float y = xy * sin(sliceAngle);

                // Normals
                float nx = x / radius;
                float ny = y / radius;
                float nz = z / radius;

                // Coordenades de textura
                float u = (float)j / slices;
                float v = (float)i / stacks;

                vertices.push_back({x, y, z, nx, ny, nz, u, v});
            }
        }

        // Generar els índexs
        for (int i = 0; i < stacks; ++i) {
            for (int j = 0; j < slices; ++j) {
                int first = i * (slices + 1) + j;
                int second = first + slices + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }
    }
};