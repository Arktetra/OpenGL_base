#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../includes/GLAD/glad.h"

#include <vector>

namespace Buffer {
    void create_VBO(std::vector<float> vertices, int draw_type);
    unsigned create_VAO(std::vector<float> vertices, int draw_type);
    void create_EBO(std::vector<int> indices, int draw_type);
    unsigned create_VAO(std::vector<float> vertices, std::vector<int> indices, int draw_type);
    void bind(unsigned VAO);
    void unbind();
};
#endif