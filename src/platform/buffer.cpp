#include "./buffer.hpp"

void Buffer::create_VBO(std::vector<float> vertices, int draw_type) {
    unsigned VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), draw_type);
}

unsigned Buffer::create_VAO(std::vector<float> vertices, int draw_type) {
    Buffer::create_VBO(vertices, draw_type);
    
    unsigned VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    return VAO;
}

void Buffer::create_EBO(std::vector<int> indices, int draw_type) {
    unsigned EBO;

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), draw_type);
}

unsigned Buffer::create_VAO(
    std::vector<float> vertices,
    std::vector<int> indices,
    int draw_type
) {
    unsigned VAO = Buffer::create_VAO(vertices, draw_type);

    Buffer::create_EBO(indices, draw_type);

    return VAO;
}

void Buffer::bind(unsigned VAO) {
    glBindVertexArray(VAO);
}

void Buffer::unbind() {
    glBindVertexArray(0);
}