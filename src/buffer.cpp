#include "./buffer.hpp"

/**
 * @brief create a vertex buffer object
 * 
 * @param vertices data to draw.
 * @param draw_type specifies the graphics card how to manage the given data.
 */
void Buffer::create_VBO(std::vector<float> vertices, int draw_type) {
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), draw_type);
}

/**
 * @brief create a vertex array object.
 */
void Buffer::create_VAO() {
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
}

/**
 * @brief create am element buffer object.
 * 
 * @param indices index of the data to draw.
 * @param draw_type specifies the graphics card how to manage the given data.
 */
void Buffer::create_EBO(std::vector<int> indices, int draw_type) {
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), draw_type);
}

/**
 * @brief Construct a new Buffer:: Buffer object without EBO.
 * 
 * @param vertices data to draw.
 * @param draw_type specifies the graphics card how to manage the given data.
 */
Buffer::Buffer(std::vector<float> vertices, int draw_type) {
    create_VBO(vertices, draw_type);
    create_VAO();
}

/**
 * @brief Construct a new Buffer:: Buffer object.
 * 
 * @param vertices data to draw.
 * @param indices index of the data to draw.
 * @param draw_type specifies the graphics card how to manage the given data.
 */
Buffer::Buffer(std::vector<float> vertices, std::vector<int> indices, int draw_type) {
    create_VBO(vertices, draw_type);
    create_VAO();
    create_EBO(indices, draw_type);
}

/**
 * @brief bind the vertex array object.
 * 
 */
void Buffer::bind() {
    glBindVertexArray(this->VAO);
}

/**
 * @brief Destroy the Buffer:: Buffer object.
 * 
 */
Buffer::~Buffer() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}