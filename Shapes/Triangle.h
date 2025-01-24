class Triangle {
public:
    static const float vertices[];
    static const unsigned int indices[];
};

const float Triangle::vertices[] = {
    // Coordenades         // Color           // Textura    // Normals
    -0.5f,  0.0f,  0.5f,  0.5f, 0.0f, 0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
    -0.5f,  0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
     0.5f,  0.0f, -0.5f,  0.0f, 0.5f, 0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
     0.5f,  0.0f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
     0.0f,  0.8f,  0.0f,  0.0f, 0.5f, 0.5f,  0.5f, 1.0f,   0.0f,  0.4472f,  0.8944f, // Vertex superior
};

const unsigned int Triangle::indices[] = {
    0,1,2,
    0,2,3,
    0,1,4,
    1,2,4,
    2,3,4,
    3,0,4
};