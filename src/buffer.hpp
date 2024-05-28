#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "./includes/GLAD/glad.h"

#include <vector>

class Buffer {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    void create_VBO(std::vector<float> vertices, int draw_type);
    void create_VAO();
    void create_EBO(std::vector<int> indices, int draw_type);

    public:
    Buffer(std::vector<float> vertices, int draw_type);
    Buffer(std::vector<float> vertices, std::vector<int> indices, int draw_type);
    ~Buffer();
    void bind();
    unsigned int get_VBO();
    unsigned int get_VAO();
    unsigned int get_EBO();
};
#endif